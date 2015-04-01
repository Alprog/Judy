
#include "Meta.h"

Meta* Meta::Instance()
{
    static Meta instance;
    return &instance;
}
