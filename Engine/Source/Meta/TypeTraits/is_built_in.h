
#pragma once

template <typename T>
struct is_built_in
{
    static const bool value = false;
};

template <>
struct is_built_in<bool>
{
    static const bool value = true;
};

template <>
struct is_built_in<int>
{
    static const bool value = true;
};

template <>
struct is_built_in<float>
{
    static const bool value = true;
};

template <>
struct is_built_in<char*>
{
    static const bool value = true;
};
