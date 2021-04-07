#include "Block.h"

void Block::destroyBlock()
{
	//play sound
	//remove from lists
}

const char* Block::getHitSoundPath()
{
	return _soundPath;
}

const char* Block::getBreakSoundPath()
{
	return _breakPath;
}
