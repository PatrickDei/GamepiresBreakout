#pragma once
#include "Level.h"
#include <vector>

using namespace std;

class LevelInitializer
{
private:
	vector<Level> _levels;

public:
	vector<BreakpointObject*> getLevel(int levelID);
};

