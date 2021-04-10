#pragma once
#include "Level.h"

const int windowWidth = 1600;
const int windowHeight = 900;

class LevelController
{
private:
	Level _levelLoader;
	int _currentLevel;

	void adjustBlockWidth(std::vector<BreakpointObject*>& objects, int gap, int columnCount, int columnSpacing);

public:
	LevelController() : _currentLevel(1) {}

	std::vector<BreakpointObject*> loadBlocksForNextLevel();
};