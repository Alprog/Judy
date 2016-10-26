
#include <Singleton.h>
#include <string>

class CrossCompiler : public Singleton<CrossCompiler>
{
    friend class SingletonType;

private:
    CrossCompiler();

public:
    void Translate(std::string hlslText);
};
