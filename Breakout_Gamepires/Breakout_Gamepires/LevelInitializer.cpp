#include "LevelInitializer.h"

vector<BreakpointObject*> LevelInitializer::getLevel(int levelID)
{
    return _levels[levelID].getObjectsForLevel(levelID);
}
