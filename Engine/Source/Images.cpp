
#include "Images.h"

#include <iostream>
#include <fstream>

#include "../../3rd-party/libpng/Source/png.h"

#define PNGSIGSIZE 8

bool validate(std::istream& source)
{
    png_byte pngsig[PNGSIGSIZE];

    source.read((char*)pngsig, PNGSIGSIZE);

    if (source.good())
    {
        auto cmp = png_sig_cmp(pngsig, 0, PNGSIGSIZE);
        if (cmp == 0)
        {
            return true;
        }
    }

    return false;
}

void readData(png_structp pngPtr, png_bytep data, png_size_t length)
{
    auto stream = (std::istream*)png_get_io_ptr(pngPtr);
    stream->read((char*)data, length);
}

Image* Images::loadPng(std::string path)
{
    std::ifstream fstream { path, std::ios::binary };
    if (fstream.is_open())
    {
        if (validate(fstream))
        {
            auto pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
            auto infoPtr = png_create_info_struct(pngPtr);

            if (setjmp(png_jmpbuf(pngPtr)))
            {
                return nullptr;
            }

            png_set_read_fn(pngPtr, (png_voidp)&fstream, readData);

            png_set_sig_bytes(pngPtr, PNGSIGSIZE);
            png_read_info(pngPtr, infoPtr);

            auto imgWidth = png_get_image_width(pngPtr, infoPtr);
            auto imgHeight = png_get_image_height(pngPtr, infoPtr);
            auto bitdepth = png_get_bit_depth(pngPtr, infoPtr);
            auto channels = png_get_channels(pngPtr, infoPtr);
            auto color_type = png_get_color_type(pngPtr, infoPtr);

            printf("width %i, heigth %i, bitdepth %i, channels %i, type %i",
                   imgWidth, imgHeight, bitdepth, channels, color_type);
            fflush(stdout);

            const unsigned int stride = imgWidth * bitdepth * channels / 8;

            auto image = new Image();
            image->width = imgWidth;
            image->height = imgHeight;
            image->data = new unsigned char[stride * imgHeight];

            auto rowPtrs = new png_bytep[imgHeight];
            for (size_t i = 0; i < imgHeight; i++)
            {
                //png_uint_32 q = (imgHeight - i - 1) * stride;
                //rowPtrs[i] = (png_bytep)image->data + q;
                rowPtrs[i] = (png_bytep)image->data + i * stride;
            }

            png_read_image(pngPtr, rowPtrs);

            delete[] (png_bytep)rowPtrs;
            png_destroy_read_struct(&pngPtr, &infoPtr, nullptr);

            return image;
        }
    }

    return nullptr;
}
