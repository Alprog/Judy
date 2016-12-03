
#pragma once

template <typename T>
class Ref;

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

//---

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

//---

template <typename T>
class List;

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

//---

template <typename T1, typename T2>
class Map;

template <typename T>
struct is_map
{
    static const bool value = false;
};

template <typename T1, typename T2>
struct is_map<Map<T1, T2>>
{
    static const bool value = true;
};
