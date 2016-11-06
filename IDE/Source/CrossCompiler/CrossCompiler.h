
#include <Singleton.h>
#include <string>
#include <QByteArray>
#include "Render/Shader.h"

class CrossCompiler : public Singleton<CrossCompiler>
{
    friend class SingletonType;

    enum class Stage
    {
        Vertex
    };

private:
    CrossCompiler();

public:
    QByteArray HlslToSpirv(std::string hlslText, Shader::Type type);
    std::string SpirvToHumanReadable(QByteArray spirvBinary);
    std::string SpirvToGlsl(QByteArray spirvBinary);
};
