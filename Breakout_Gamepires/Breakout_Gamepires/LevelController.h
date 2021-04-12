#pragma once
#include "Level.h"

/// <summary>
/// Window dimensions - used in main and BreakpointController
/// </summary>
const int windowWidth = 1600;
const int windowHeight = 900;

/// <summary>
/// Class that keeps track of levels
/// </summary>
class LevelController
{
private:
	Level _levelLoader;
	int _currentLevel;

	/// <summary>
	/// Adjusts blocks width's based on window size
	/// </summary>
	/// <param name="objects"> Blocks to adjust </param>
	/// <param name="gap"> Space between window border & adjacent blocks </param>
	/// <param name="columnCount"> Number of block columns </param>
	/// <param name="columnSpacing"> Space between each block column </param>
	void adjustBlockWidth(std::vector<BreakpointObject*>& objects, int gap, int columnCount, int columnSpacing);

public:
	/// Set first level as 1
	LevelController() : _currentLevel(1) {}

	/// <summary>
	/// Determines next level and requests blocks for said level
	/// </summary>
	/// <returns> Blocks for the new level </returns>
	std::vector<BreakpointObject*> loadBlocksForNextLevel();
};