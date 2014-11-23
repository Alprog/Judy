
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

    SubStruct(int v)
        : e { v }
    {
    }
};

struct TestStruct
{
    friend TypeMeta<TestStruct>;

    int a;
    int b;
    int* c;
    SubStruct d;
    SubStruct* dd;
    std::string g;

public:
    TestStruct(int a, int b, char* text, SubStruct d)
    {
        this->a = a;
        this->b = b;
        this->c = new int(8);
        this->d = d;
        this->g = text;
        this->dd = new SubStruct(17);
    }

private:
    TestStruct()
    {
        this->dd = new SubStruct(22);
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
