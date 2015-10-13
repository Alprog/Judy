
#include "PropertyInfo.h"

PropertyInfo::PropertyInfo(TokenGroup& tokens)
{
    attributes = tokens.extractAttributes();
    name = tokens.extractLast()->getName();
}

void PropertyInfo::addMethod(TokenGroup& tokens)
{
    MethodInfo methodInfo(tokens);
    if (methodInfo.returnType.name != "void" && methodInfo.arguments.size() == 0)
    {
        getter = methodInfo;
    }
    else if (methodInfo.returnType.name == "void" && methodInfo.arguments.size() == 1)
    {
        setter = methodInfo;
    }
}

bool PropertyInfo::hasGetter() const
{
    return !getter.name.empty();
}

bool PropertyInfo::hasSetter() const
{
    return !setter.name.empty();
}
