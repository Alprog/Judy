
#pragma once

#include <stdio.h>
#include <iostream>

struct Image
{
    int width;
    int height;
    unsigned char* data;
};

namespace Images
{
    Image* LoadPng(std::string path);
}
