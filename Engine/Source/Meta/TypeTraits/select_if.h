
#pragma once

template <bool, typename T1 = void, typename T2 = int>
struct select_if
{
    using type = T1;
};

template <typename T1, typename T2>
struct select_if<false, T1, T2>
{
    using type = T2;
};
