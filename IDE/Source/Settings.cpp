
#include "Settings.h"

void Settings::initMeta()
{
    auto meta = Meta::getInstance();
    ClassDefiner<Settings>(meta, "Settings")
        .constructor()
        .field("playerPath", &Settings::playerPath).attr("Serialize")
        .field("projectPath", &Settings::projectPath).attr("Serialize")
    ;
}
