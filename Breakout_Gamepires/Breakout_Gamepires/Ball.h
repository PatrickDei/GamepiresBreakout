#pragma once
#include "BreakpointObject.h"
#include <math.h>
#include "tinyxml2.h"
#include <time.h>

const float PI = 3.141592654;

class Ball : public BreakpointObject
{
private:
	float _speed;
	// angle of ball - always positive [0, 360>
	float _direction;

public:
	Ball(float x = 0, float y = 0) : BreakpointObject(x, y) {
		// parameters load
		tinyxml2::XMLDocument _parameters;
		_parameters.LoadFile("Params/Parameters.xml");
		tinyxml2::XMLElement* rootElement = _parameters.RootElement();

		// speed assignment
		_speed = rootElement->FirstChildElement("defaultBallSpeed")->FloatText();
		
		// direction calculation
		tinyxml2::XMLElement* angle = rootElement->FirstChildElement("startingAngles");
		int leftAngle = angle->IntAttribute("leftAngle");
		int rightAngle = angle->IntAttribute("rightAngle");

		srand((unsigned int)time(NULL));
		_direction = rand() % leftAngle + rightAngle;
	}

	float getSpeed();

	void setSpeed(float value);

	float getDirectionAngle();

	void getDirections(float& x, float& y);

	void setDirection(float angle);
};