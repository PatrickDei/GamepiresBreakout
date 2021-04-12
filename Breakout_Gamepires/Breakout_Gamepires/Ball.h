#pragma once
#include "BreakpointObject.h"
#include <math.h>
#include <time.h>
#include "tinyxml2.h"

const double PI = 3.141592654;

/// <summary>
/// Class used for the ball instance
/// </summary>
class Ball : public BreakpointObject
{
private:
	/// Angle of ball - always positive [0, 360>
	float _direction;
	float _speed;

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
		// check if exact angle is assigned (in Parameters.xml) -> leftAngle == rightAngle
		if (range != 0)
			_direction = rand() % range + rightAngle;
		else
			_direction = leftAngle;
	}

	float getSpeed();

	void setSpeed(float value);

	float getDirectionAngle();

	/// Assigns x & y values of ball direction
	void getDirections(float& x, float& y);

	/// Corrects the angle if it is set in negative value or value greater than 360 degrees
	void setDirection(float angle);

	/// <summary>
	/// Flips the direction of ball around an axis
	/// </summary>
	/// <param name="axis"> Axis around which to turn the ball around </param>
	void invertDirectionVector(char axis);

	vector<Point> getEdgePoints() override;

	/// Updates ball's position based on passed time so it is consistent no matter the framerate
	void update(float dt);
};