
#include "Meta.h"

Meta* Meta::Instance()
{
    static Meta instance;
    return &instance;
}

/*template <typename T>
MetaDefiner<T>* Meta::Define()
{
    return MetaDefiner<T>();
}
*/
