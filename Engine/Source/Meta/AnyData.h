
#pragma once

class ITypeMeta;

template <typename T>
ITypeMeta* TypeMetaOf();

struct IAnyData
{
    virtual ~IAnyData() {}

    virtual ITypeMeta* GetType() = 0;
    virtual IAnyData* copy() = 0;
};

template <typename T>
struct AnyData : public IAnyData
{
    T data;

    AnyData(T const& data)
        : data(data)
    {
    }

    virtual ITypeMeta* GetType() override
    {
        return TypeMetaOf<T>();
    }

    virtual IAnyData* copy() override
    {
        return new AnyData<T>(data);
    }
};
