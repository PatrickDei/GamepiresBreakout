#include "Block.h"

bool Block::loseHealth()
{
	_blockHealth--;
	if (_blockHealth == 0)
		return true;
	return false;
}

int Block::getScore()
{
	return _score;
}

char Block::getId()
{
	return _ID;
}

const char* Block::getHitSoundPath()
{
	return _soundPath->c_str();
}

const char* Block::getBreakSoundPath()
{
	return _breakPath->c_str();
}

const char* Block::getTexturePath()
{
	return _texturePath->c_str();
}
