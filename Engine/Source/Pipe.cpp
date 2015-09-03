
#include "Pipe.h"

#ifdef WIN
    #include <io.h>
#else
    #include <unistd.h>
    #include <fcntl.h>
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

#if !WIN
    // make none-blocking
    auto flags = fcntl(descriptors[READ], F_GETFL);
    fcntl(descriptors[READ], F_SETFL, flags | O_NONBLOCK);
#endif
}

Pipe::~Pipe()
{
    close(descriptors[READ]);
    close(descriptors[WRITE]);
}

std::string Pipe::readText()
{
    const int MAX = 1024;
    std::string result;
    char buffer[MAX + 1];
    int f = descriptors[READ];
#if WIN
    while (!eof(f))
    {
        int count = read(f, buffer, MAX);
        buffer[count] = 0;
        result += buffer;
    }
#else
    int count = 0;
    do
    {
        count = read(f, buffer, MAX);
        if (count > 0)
        {
            buffer[count] = 0;
            result += buffer;
        }
    }
    while (count == MAX);
#endif
    return result;
}

void operator>>(Pipe& pipe, std::string& string)
{
    string += pipe.readText();
}
