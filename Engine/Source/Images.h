
#pragma once

#include <stdio.h>
#include <iostream>
#include <Path.h>

struct Image
{
    int width;
    int height;
    unsigned char* data;

    size_t getSize() { return width * height * 4; };
};

namespace Images
{
    Image* loadPng(Path path);
}
