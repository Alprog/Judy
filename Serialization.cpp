// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <exception>
#include "math.h"
#include <vector>
#include <typeinfo>

class Vector2
{
public:
	Vector2() {}
	int Foo(int x, int y) 
	{ 
		return x + X + y + Y; 
	}
	int X, Y;

	void Bar(int x, int y) {}
};

class Variant
{
public:
	static const Variant empty;

	Variant(void)
		: size {0}
		, data {nullptr}
	{
	}

	template <typename Type>
	Variant(Type value)
	{
		data = new Type();
		*(Type*)data = value;
		size = sizeof(value);
	}

	template <typename Type>
	operator Type()
	{
		return *(Type*)data;
	}

	size_t size;
	void* data;
};

const Variant Variant::empty = Variant();

template <size_t... I>
struct index_sequence {};

template <size_t N, size_t... I>
struct make_index_sequence : public make_index_sequence<N - 1, N - 1, I...> {};

template <size_t... I>
struct make_index_sequence<0, I...> : public index_sequence<I...>{};

class MetaField
{
public:
	virtual void set(void* object, void* value) = 0;
	virtual void* get(void* object) = 0;
	char* name;
};

template <typename ClassType, typename FieldType>
class MetaFieldConcrete : public MetaField
{
public:
	MetaFieldConcrete(char* name, FieldType ClassType::*pointer)
	{
		this->name = name;
		this->pointer = pointer;
	}

	virtual void set(void* object, void* value) override
	{
		(ClassType*)object->*pointer = *(FieldType*)value;
	}

	virtual void* get(void* object) override
	{
		return &((ClassType*)object->*pointer);
	}

	FieldType ClassType::*pointer;
};

class MetaMethod
{
public:
	virtual Variant Invoke(void* object, std::vector<Variant> args) = 0;
	virtual std::vector<const type_info*> GetArgTypes() = 0;
	char* name;
};

template <typename ClassType, typename ReturnType, typename... ArgTypes>
class MetaMethodConcreteBase : public MetaMethod
{
public:
	static const int ArgCount = sizeof...(ArgTypes);

	virtual std::vector<const type_info*> GetArgTypes() override
	{
		return { &(typeid(ArgTypes))... };
	}

	template <int... I>
	ReturnType RealInvoke(void* object, std::vector<Variant> args, index_sequence<I...>)
	{
		return ((ClassType*)object->*pointer)(args.at(I)...);
	}

	ReturnType(ClassType::*pointer)(ArgTypes...);
};

template <typename ClassType, typename ReturnType, typename... ArgTypes>
class MetaMethodConcrete : public MetaMethodConcreteBase<ClassType, ReturnType, ArgTypes...>
{
public:
	Variant Invoke(void* object, std::vector<Variant> args) override
	{
		if (args.size() == sizeof...(ArgTypes))
		{
			return RealInvoke(object, args, make_index_sequence<sizeof...(ArgTypes)>());
		}
		else
		{
			throw new std::exception();
		}
	}
};

template <typename ClassType, typename... ArgTypes>
class MetaMethodConcrete<ClassType, void, ArgTypes...> : public MetaMethodConcreteBase<ClassType, void, ArgTypes...>
{
public:
	Variant Invoke(void* object, std::vector<Variant> args) override
	{
		if (args.size() == sizeof...(ArgTypes))
		{
			RealInvoke(object, args, make_index_sequence<sizeof...(ArgTypes)>());
			return Variant::empty;
		}
		else
		{
			throw new std::exception();
		}
	}
};

template <typename ClassType>
class MetaClass
{
public:
	static MetaClass* Instance()
	{
		static MetaClass<ClassType> instance;
		return &instance;
	}

	template <typename FieldType>
	MetaClass* field(char* name, FieldType ClassType::*pointer)
	{
		auto field = new MetaFieldConcrete<ClassType, FieldType>(name, pointer);
		fields.push_back(field);
		return this;
	}

	template <typename ReturnType, typename... ArgTypes>
	MetaClass* method(char* name, ReturnType(ClassType::*pointer)(ArgTypes...))
	{
		auto method = new MetaMethodConcrete<ClassType, ReturnType, ArgTypes...>();
		method->name = name;
		method->pointer = pointer;
		methods.push_back(method);
		return this;
	}

	void* create()
	{
		return new ClassType();
	}

	void set(void* object, char* name, void* value)
	{
		for (auto field : fields)
		{
			if (field->name == name)
			{
				field->set(object, value);
			}
		}
	}
	
	void* get(void* object, char* name)
	{
		for (auto field : fields)
		{
			if (field->name == name)
			{
				return field->get(object);
			}
		}
		return 0;
	}

	Variant invoke(void* object, char* name, std::vector<Variant> args)
	{
		for (auto method : methods)
		{
			if (method->name == name)
			{
				return method->Invoke(object, args);
			}
		}
	}

	std::vector<MetaField*> fields;
	std::vector<MetaMethod*> methods;
};


int _tmain(int argc, _TCHAR* argv[])
{
	MetaClass<Vector2>::Instance()
		->field("X", &Vector2::X)
		->field("Y", &Vector2::Y)
		->method("Foo", &Vector2::Foo)
		->method("Bar", &Vector2::Bar);

	auto metaClass = MetaClass<Vector2>::Instance();
	auto vector = metaClass->create();
	
	auto name = metaClass->methods[0]->GetArgTypes()[0]->name();

	int x = 3; int y = 4;
	metaClass->set(vector, "X", &x);
	metaClass->set(vector, "Y", &y);
	
	int result = metaClass->invoke(vector, "Foo", {0, 1});

	return 0;
}
