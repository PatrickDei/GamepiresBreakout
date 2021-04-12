#include "Player.h"

void Player::loseHealth()
{
	_health--;
}

void Player::setPosX(float value)
{
	if (value >= 0 && value < windowWidth - _width)
		_positionX = value;
}

void Player::setPosition(float x, float y)
{
	if (x >= 0 && x < windowWidth - _width && y >= 0) {
		_positionX = x;
		_positionY = y;
	}
}

int Player::getScore()
{
	return _score;
}

int Player::getHealth()
{
	return _health;
}