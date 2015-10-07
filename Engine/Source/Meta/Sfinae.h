
#pragma once
#include <type_traits>
#include "select_if.h"
#include <vector>
#include <unordered_map>

template <typename T>
class List;

template <typename T>
class DeepPointer;

template <typename T>
struct is_deep_pointer
{
    static const bool value = false;
};

template <typename T>
struct is_deep_pointer<DeepPointer<T>>
{
    static const bool value = true;
};

template <typename T>
struct is_map
{
    static const bool value = false;
};

template <typename T1, typename T2>
struct is_map<std::unordered_map<T1, T2>>
{
    static const bool value = true;
};

template <typename T>
struct is_list
{
    static const bool value = false;
};

template <typename T>
struct is_list<List<T>>
{
    static const bool value = true;
};

//-----------------

template <typename T>
struct fulldecay
{
    using type = typename std::decay<T>::type;
};

template <typename T>
struct fulldecay<T*>
{
    using type = typename std::decay<typename fulldecay<T>::type*>::type;
};

template <typename T> struct fulldecay<T&> : public fulldecay<T> {};
template <typename T> struct fulldecay<T&&> : public fulldecay<T> {};
template <typename T> struct fulldecay<T const> : public fulldecay<T> {};

//-----------------

template<class T>
struct is
{
    enum { RealPointer = std::is_pointer<T>::value };
    enum { DeepPointer = is_deep_pointer<T>::value };
    enum { RealClass = std::is_class<T>::value };
    enum { Abstract = std::is_abstract<T>::value };
    enum { Polymorphic = std::is_polymorphic<T>::value };
    enum { List = is_list<T>::value };
    enum { Map = is_map<T>::value };

    enum { Pointer = RealPointer || DeepPointer };
    enum { Class = RealClass && !DeepPointer };

    enum { ClassOrPointer = Class || Pointer };
    enum { AbstractClassOrRealPointer = Abstract || RealPointer };

    enum { Void = std::is_same<T, void>::value };
    enum { PointerToVoid = std::is_same<T, void*>::value };
    enum { PointerToPolymorhic = RealPointer && std::is_polymorphic<typename std::remove_pointer<T>::type>::value };
    enum { PointerToAbstract = RealPointer && std::is_abstract<typename std::remove_pointer<T>::type>::value };
    enum { AllowDereferencing = !Abstract && !Void };
};

#define IF(T, C) typename std::enable_if<is<T>::C>::type
#define IF_NOT(T, C) typename std::enable_if<!is<T>::C>::type

#define SELECT_IF(T, C, T1, T2) typename select_if<is<T>::C, T1, T2>::type
