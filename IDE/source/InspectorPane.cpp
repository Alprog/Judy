
#include "InspectorPane.h"

InspectorPane::InspectorPane()
    : QDockWidget("Inspector", 0, 0)
{
    setObjectName("Inspector");
    setMinimumWidth(250);
}

InspectorPane::~InspectorPane()
{
}
