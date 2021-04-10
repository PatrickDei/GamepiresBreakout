#pragma once
#include "SoftBlock.h"
#include <vector>

class Level
{
private:
	std::vector<BreakpointObject*> _blocks;

	std::vector<BreakpointObject*> generateLevel(std::vector<char> characters);

public:
	std::vector<BreakpointObject*> getObjectsForLevel(int levelID);
};