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

class FieldMeta
{
public:
	virtual void set(void* object, void* value) = 0;
	virtual void* get(void* object) = 0;
	char* name;
};

template <typename ClassType, typename FieldType>
class ConcreteFieldMeta : public FieldMeta
{
public:
	ConcreteFieldMeta(char* name, FieldType ClassType::*pointer)
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

class MethodMeta
{
public:
	virtual Variant Invoke(void* object, std::vector<Variant> args) = 0;
	virtual std::vector<const type_info*> GetArgTypes() = 0;
	char* name;
};

template <typename ClassType, typename ReturnType, typename... ArgTypes>
class ConcreteMethodMetaBase : public MethodMeta
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
class ConcreteMethodMeta : public ConcreteMethodMetaBase<ClassType, ReturnType, ArgTypes...>
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
class ConcreteMethodMeta<ClassType, void, ArgTypes...> : public ConcreteMethodMetaBase<ClassType, void, ArgTypes...>
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
class ClassMeta
{
public:
	static ClassMeta* Instance()
	{
		static ClassMeta<ClassType> instance;
		return &instance;
	}

	template <typename FieldType>
	ClassMeta* field(char* name, FieldType ClassType::*pointer)
	{
		auto field = new ConcreteFieldMeta<ClassType, FieldType>(name, pointer);
		fields.push_back(field);
		return this;
	}

	template <typename ReturnType, typename... ArgTypes>
	ClassMeta* method(char* name, ReturnType(ClassType::*pointer)(ArgTypes...))
	{
		auto method = new ConcreteMethodMeta<ClassType, ReturnType, ArgTypes...>();
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

	std::vector<FieldMeta*> fields;
	std::vector<MethodMeta*> methods;
};


int _tmain(int argc, _TCHAR* argv[])
{
	ClassMeta<Vector2>::Instance()
		->field("X", &Vector2::X)
		->field("Y", &Vector2::Y)
		->method("Foo", &Vector2::Foo)
		->method("Bar", &Vector2::Bar);

	auto vectorMeta = ClassMeta<Vector2>::Instance();
	auto vector = vectorMeta->create();
	
	auto name = vectorMeta->methods[0]->GetArgTypes()[0]->name();

	int x = 3; int y = 4;
	vectorMeta->set(vector, "X", &x);
	vectorMeta->set(vector, "Y", &y);
	
	int result = vectorMeta->invoke(vector, "Foo", { 0, 1 });

	return 0;
}
