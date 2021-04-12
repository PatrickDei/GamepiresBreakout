#pragma once
#include "SoftBlock.h"
#include "MediumBlock.h"
#include "HardBlock.h"
#include "ImpenetrableBlock.h"
#include <vector>

/// <summary>
/// Level class holds blocks
/// Can load new level & return desired level
/// </summary>
class Level
{
private:
	std::vector<BreakpointObject*> _blocks;

	/// <summary>
	/// Converts characters into Derived BreakpointObjects
	/// </summary>
	/// <param name="characters"> List of characters from Items.xml - determines level layout </param>
	/// <returns> List of Blocks </returns>
	std::vector<BreakpointObject*> generateLevel(std::vector<char> characters);

public:
	/// <summary>
	/// Generates level for desired level ID
	/// </summary>
	/// <param name="levelID"> Desired level - int </param>
	/// <returns> List of blocks </returns>
	std::vector<BreakpointObject*> getObjectsForLevel(int levelID);
};