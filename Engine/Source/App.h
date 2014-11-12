
#pragma once

#include <set>
#include "Window.h"

#include "Meta/TypeMeta.h"

struct SubStruct
{
    friend TypeMeta<SubStruct>;

    int e;

    SubStruct()
        : e { 0 }
    {
    }
};

struct TestStruct
{
    friend TypeMeta<TestStruct>;

    int a;
    int b;
    char* c;
    SubStruct d;

public:
    TestStruct(int a, int b, char* c, SubStruct d)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }

private:
    TestStruct()
    {
    }
};

class App
{
    friend TypeMeta<App>;

public:
    static App* Instance();

    void StartMainLoop();

    void AddWindow(Window* window);
    void RemoveWindow(Window* window);

private:
    void UpdateCollection();

    std::set<Window*> Windows;
    std::set<Window*> AddedWindows;
    std::set<Window*> RemovedWindows;
};
