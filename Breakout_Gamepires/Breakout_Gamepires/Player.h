#pragma once
#include "tinyxml2.h"
#include "Wall.h"

class Player : public Wall
{
private:
	int _score;
	int _health;

public:
	Player(float x = 0, float y = 0, float endX = 0, float endY = 0) : _score(0), Wall(x, y, endX, endY){
		tinyxml2::XMLDocument parameters;
		parameters.LoadFile("Parameters/Parameters.xml");
		_health = parameters.RootElement()->FirstChildElement("totalPlayerHealth")->IntText();
	}

	void loseHealth();
};