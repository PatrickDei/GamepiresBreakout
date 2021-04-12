#pragma once
#include "BreakpointObject.h"
#include "LevelController.h"
#include "tinyxml2.h"

/// <summary>
/// Player class defines player behaviour
/// additionally stores score and health
/// </summary>
class Player : public BreakpointObject
{
private:
	int _score;
	int _health;

public:
	Player(float x = 0, float y = 0, float width = 0, float height = 0) : _score(0), BreakpointObject(x, y, width, height){
		tinyxml2::XMLDocument parameters;
		parameters.LoadFile("Parameters/Parameters.xml");
		_health = parameters.RootElement()->FirstChildElement("totalPlayerHealth")->IntText();
	}

	int getScore();

	int getHealth();	
	
	/// Lowers _health member by 1
	void loseHealth();

	void setPosX(float value) override;

	void setPosition(float x, float y) override;
};