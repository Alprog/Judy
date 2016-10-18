
#pragma once

class ITypeMeta;

template <typename T>
ITypeMeta* typeMetaOf();

struct IAnyData
{
    virtual ~IAnyData() {}

    virtual ITypeMeta* getType() = 0;
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

    virtual ITypeMeta* getType() override
    {
        return typeMetaOf<T>();
    }

    virtual IAnyData* copy() override
    {
        return new AnyData<T>(data);
    }
};
