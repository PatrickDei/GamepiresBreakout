#pragma once

class BreakpointObject
{
protected:
	float _positionX;
	float _positionY;

	BreakpointObject(float x = 0, float y = 0) : _positionX(x), _positionY(y) {}

public:
	float getPosX();

	void setPosX(float value);

	float getPosY();

	void setPosY(float value);

	void setPosition(float x, float y);
};