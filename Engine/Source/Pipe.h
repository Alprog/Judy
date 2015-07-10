
#pragma once

#include <iostream>
#include <string>

class Pipe
{
public:
    Pipe(FILE* file);
    ~Pipe();

    std::string readText();
    friend void operator>>(Pipe& pipe, std::string& string);

private:
    int descriptors[2];
};
