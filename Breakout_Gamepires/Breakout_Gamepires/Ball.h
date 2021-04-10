#pragma once
#include "BreakpointObject.h"
#include <math.h>
#include "tinyxml2.h"
#include <time.h>

const double PI = 3.141592654;

class Ball : public BreakpointObject
{
private:
	float _speed;
	// angle of ball - always positive [0, 360>
	float _direction;

public:
	Ball(float x = 0, float y = 0, float radius = 10) : BreakpointObject(x, y, radius, radius) {
		// parameters load
		tinyxml2::XMLDocument _parameters;
		_parameters.LoadFile("Parameters/Parameters.xml");
		tinyxml2::XMLElement* rootElement = _parameters.RootElement();

		// speed assignment
		rootElement->FirstChildElement("defaultBallSpeed")->QueryFloatText(&_speed);
		
		// direction calculation
		tinyxml2::XMLElement* angle = rootElement->FirstChildElement("startingAngles");
		int leftAngle = angle->IntAttribute("leftAngle");
		int rightAngle = angle->IntAttribute("rightAngle");

		int range = leftAngle - rightAngle;
		srand((unsigned int)time(NULL));
		if (range != 0)
			_direction = rand() % range + rightAngle;
		else
			_direction = leftAngle;
	}

	float getSpeed();

	void setSpeed(float value);

	float getDirectionAngle();

	void getDirections(float& x, float& y);

	void setDirection(float angle);

	void invertDirectionVector(const char* axis);

	vector<Point> getEdgePoints() override;
};