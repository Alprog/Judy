
#include "Images.h"

#include <fstream>

#include "../../3rd-Party/libpng/source/png.h"

#define PNGSIGSIZE 8

bool validate(std::istream& source)
{
    auto t = source.rdstate();

    png_byte pngsig[PNGSIGSIZE];
    int is_png = 0;

    //source.read((char*)pngsig, PNGSIGSIZE);

    source >> pngsig;

    //printf((char*)(pngsig[0]));
    //fflush(stdout);

    auto a = source.rdstate();

    if (!source.good())
    {
        return false;
    }
    is_png = png_sig_cmp(pngsig, 0, PNGSIGSIZE);
    return (is_png == 0);
}


void Images::LoadPng(std::wstring path)
{
    std::ifstream file {path};
    if (file.is_open())
    {
        bool a = validate(file);

        printf("png is open");
        fflush(stdout);

        if (a)
        {
            printf("png is valid");
            fflush(stdout);
        }

    }
}
