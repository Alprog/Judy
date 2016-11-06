
#include <Singleton.h>
#include <string>
#include <QByteArray>

class CrossCompiler : public Singleton<CrossCompiler>
{
    friend class SingletonType;

private:
    CrossCompiler();

public:
    QByteArray HlslToSpirv(std::string hlslText);
    std::string SpirvToHumanReadable(QByteArray spirvBinary);
    std::string SpirvToGlsl(QByteArray spirvBinary);
};
