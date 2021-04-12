#pragma once
#include "Block.h"

/// <summary>
/// Impenetrable block class
/// passes char ID to base class
/// overrides health
/// </summary>
class ImpenetrableBlock : public Block
{
public:
	ImpenetrableBlock() : Block('I') {}

	/// <summary>
	/// Override for the default method to substract block health
	/// </summary>
	/// <returns> False </returns>
	bool loseHealth() override;
};

