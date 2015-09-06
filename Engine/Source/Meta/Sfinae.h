
#pragma once
#include <type_traits>
#include <vector>

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
struct is_vector
{
    static const bool value = false;
};

template <typename T>
struct is_vector<std::vector<T>>
{
    static const bool value = true;
};

template<class T>
struct is
{
    enum { RealPointer = std::is_pointer<T>::value };
    enum { DeepPointer = is_deep_pointer<T>::value };
    enum { RealClass = std::is_class<T>::value };
    enum { Abstract = std::is_abstract<T>::value };
    enum { Vector = is_vector<T>::value };

    enum { Pointer = RealPointer || DeepPointer };
    enum { Class = RealClass && !DeepPointer };

    enum { ClassOrPointer = Class || Pointer };
    enum { AbstractClassOrRealPointer = Abstract || RealPointer };

    enum { Void = std::is_same<T, void>::value };
    enum { PointerToVoid = std::is_same<T, void*>::value };
    enum { PointerToAbstract = std::is_abstract<typename std::remove_pointer<T>::type>::value };
    enum { AllowDereferencing = (RealPointer && !PointerToAbstract && !PointerToVoid) || DeepPointer };

};

#define IF(T, C) typename std::enable_if<is<T>::C>::type
#define IF_NOT(T, C) typename std::enable_if<!is<T>::C>::type
