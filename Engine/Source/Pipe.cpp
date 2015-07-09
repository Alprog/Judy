
#include "Pipe.h"

#ifdef WIN
    #include <io.h>
#else
    #include <unistd.h>
#endif

#ifdef WIN
    void pipe(int* descriptors)
    {
        _pipe(descriptors, 128 * 1024, 0);
    }
#endif

#include "iostream"
#include "stdio.h"

enum Pipes
{
    READ, WRITE
};

Pipe::Pipe(FILE* file)
{
    auto save = dup(fileno(file));

    pipe(descriptors);
    dup2(descriptors[WRITE], fileno(file));
}

Pipe::~Pipe()
{
    close(descriptors[READ]);
    close(descriptors[WRITE]);
}

bool Pipe::isEof()
{
    return feof(descriptors[READ]);
}

std::string Pipe::readText()
{
    const int MAX = 1024;
    std::string result;
    char buffer[MAX + 1];
    int f = descriptors[READ];
    while (!feof(f))
    {
        int count = read(f, buffer, MAX);
        buffer[count] = 0;
        result += buffer;
    }
    return result;
}

void operator>>(Pipe& pipe, std::string& string)
{
    string += pipe.readText();
}
