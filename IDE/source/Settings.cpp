
#include "Settings.h"

void Settings::InitMeta()
{
    auto meta = Meta::Instance();
    ClassDefiner<Settings>(meta, "Settings")
        .constructor()
        .field("playerPath", &Settings::playerPath)
        .field("projectPath", &Settings::projectPath)
    ;
}
