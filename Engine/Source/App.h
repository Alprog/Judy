
#pragma once

#include <set>
#include <unordered_set>
#include "Window.h"

#include "Meta/Meta.h"
#include "Meta/TypeMeta.h"

#define __Meta__

struct __Meta__ SubStruct
{
    friend class Meta;

    int e;
    std::vector<int> arr;
    std::unordered_set<int> set;
    std::unordered_map<std::string, int> map;

    SubStruct()
        : e { 7 }
    {
    }

    SubStruct(int v)
        : e { v }
    {
    }
};

struct __Meta__ TestStruct
{
    friend class Meta;

    float a;
    int* c;
    SubStruct d;
    SubStruct* dd;
    std::string g;
    std::vector<int> arr;
    std::unordered_map<std::string, int> map;

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

protected:
    TestStruct()
    {
        this->dd = new SubStruct(22);
    }
}; 

class __Meta__ App
{
    friend class Meta;

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
