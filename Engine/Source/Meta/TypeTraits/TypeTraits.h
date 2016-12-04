
#pragma once

#include <type_traits>

#include "is_built_in.h"
#include "pointers.h"
#include "select_if.h"
#include "fulldecay.h"
#include "misc.h"

class Object;

template<class T>
struct is
{
    enum { BuiltIn = is_built_in<T>::value };
    enum { RealPointer = std::is_pointer<T>::value };
    enum { DeepPointer = is_deep_pointer<T>::value };
    enum { Ref = is_ref<T>::value };
    enum { Enum = std::is_enum<T>::value };
    enum { RealClass = std::is_class<T>::value };
    enum { Abstract = std::is_abstract<T>::value };
    enum { Void = std::is_same<T, void>::value };
    enum { Polymorphic = std::is_polymorphic<T>::value };
    enum { List = is_list<T>::value };
    enum { Map = is_map<T>::value };
    enum { Object = std::is_base_of<Object, T>::value };

    enum { Pointer = RealPointer || Ref || DeepPointer };
    enum { Class = RealClass && !Pointer };

    enum { ClassOrPointer = Class || Pointer };
    enum { PointerToObject = is<typename pointeeOf<T>::type>::Object && !DeepPointer };
    enum { PointerToPolymorhic = std::is_polymorphic<typename pointeeOf<T>::type>::value && !DeepPointer };
    enum { AllowDereferencing = !Abstract && !Void };

    enum { CustomSerializing = List || Map };
};

#define IF(T, C) typename std::enable_if<is<T>::C>::type
#define IF_NOT(T, C) typename std::enable_if<!is<T>::C>::type

#define SELECT_IF(T, C, T1, T2) typename select_if<is<T>::C, T1, T2>::type
