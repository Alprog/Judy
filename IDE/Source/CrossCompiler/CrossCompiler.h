
#include <Singleton.h>
#include <string>
#include <vector>
#include <map>
#include <QByteArray>
#include "Render/Shader.h"

class CrossCompiler : public Singleton<CrossCompiler>
{
    friend class SingletonType;

    using Pragmas = std::vector<std::pair<std::string, std::string>>;
    using EntryPoints = std::map<std::string, std::vector<std::string>>;

    struct Spirv
    {
        QByteArray vs, gs, ps;
    };

private:
    CrossCompiler();

public:
    Spirv hlslToSpirv(std::string hlslText);
    std::string spirvToHumanReadable(QByteArray spirvBinary);
    std::string spirvToGlsl(QByteArray spirvBinary);

private:
    EntryPoints getEntryPoints(std::string hlslText);
    Pragmas getPragmas(std::string hlslText);
};
