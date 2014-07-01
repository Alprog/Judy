
#pragma once

struct Color
{
    union
    {
        struct
        {
            float r;
            float g;
            float b;
            float a;
        };

        float data[4];
    };
};
