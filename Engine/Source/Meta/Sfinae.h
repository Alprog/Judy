
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
class Ref;

//---

template <typename T>
struct pointerOf
{
    using type = T*;
};

template <typename T>
struct pointerOf<T*>
{
    using type = DeepPointer<T>;
};

template <typename T>
struct pointerOf<Ref<T>>
{
    using type = DeepPointer<T>;
};

template <typename T>
struct pointerOf<DeepPointer<T>>
{
    using type = DeepPointer<T>;
};

//---

template <typename T>
struct pointeeOf
{
    using type = std::nullptr_t;
};

template <typename T>
struct pointeeOf<T*>
{
    using type = T;
};

template <typename T>
struct pointeeOf<Ref<T>>
{
    using type = typename Ref<T>::pointeeType;
};

template <typename T>
struct pointeeOf<DeepPointer<T>>
{
    using type = typename DeepPointer<T>::pointeeType;
};

//---

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
struct is_ref
{
    static const bool value = false;
};

template <typename T>
struct is_ref<Ref<T>>
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
    enum { Ref = is_ref<T>::value };
    enum { RealClass = std::is_class<T>::value };
    enum { Abstract = std::is_abstract<T>::value };
    enum { Polymorphic = std::is_polymorphic<T>::value };
    enum { List = is_list<T>::value };
    enum { Map = is_map<T>::value };

    enum { Pointer = RealPointer || Ref || DeepPointer };
    enum { Class = RealClass && !Pointer };

    enum { ClassOrPointer = Class || Pointer };

    enum { Void = std::is_same<T, void>::value };
    enum { PointerToPolymorhic = std::is_polymorphic<typename pointeeOf<T>::type>::value && !DeepPointer };
    enum { AllowDereferencing = !Abstract && !Void };

    enum { CustomSerializing = List || Map };

    enum { R = (RealPointer || Ref) && is<typename pointeeOf<T>::type>::AllowDereferencing };
};

#define IF(T, C) typename std::enable_if<is<T>::C>::type
#define IF_NOT(T, C) typename std::enable_if<!is<T>::C>::type

#define SELECT_IF(T, C, T1, T2) typename select_if<is<T>::C, T1, T2>::type
