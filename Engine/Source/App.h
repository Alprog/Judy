
#pragma once

#include <set>
#include "Window.h"

#include "Meta/Meta.h"
#include "Meta/TypeMeta.h"

struct SubStruct
{
    friend Meta;
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
    friend Meta;
    friend TypeMeta<TestStruct>;

    float a;
    int* c;
    SubStruct d;
    SubStruct* dd;
    std::string g;
    std::vector<int> arr;

private:
    int b;

public:
    TestStruct(float a, int b, char* text, SubStruct d)
    {
        this->a = a;
        this->b = b;
        this->c = new int(8);
        this->d = d;
        this->g = text;
        this->dd = new SubStruct(17);

        arr.push_back(1);
        arr.push_back(2);
        arr.push_back(3);
    }

private:
    TestStruct()
    {
        this->dd = new SubStruct(22);
    }
};

#define __Meta__

class __Meta__ App
{
    friend class Meta;
    friend class TypeMeta<Meta>;

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
