#include "Player.h"

void Player::loseHealth()
{
	_health--;
}

int Player::getScore()
{
	return _score;
}

int Player::getHealth()
{
	return _health;
}