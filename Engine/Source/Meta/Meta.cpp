
#include "Meta.h"
#include "TypeMeta.h"

#include "ClassDefiner.h"
#include "CallInfo.h"
#include "Node.h"

Meta::Meta()
{
    DefineBuildInType<bool>("bool");
    DefineBuildInType<int>("int");
    DefineBuildInType<float>("float");
    DefineBuildInType<std::string>("string");
    DefineBuildInType<char>("char");
    DefineBuildInType<double>("double");

    DefineClasses();
}
