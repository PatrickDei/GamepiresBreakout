#pragma once
#include "Level.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "LevelController.h"
#include <algorithm>


class BreakpointController
{
private:
	Ball _ball;	
	LevelController _levelController;
	vector<sf::RectangleShape> _shapes;
	vector<BreakpointObject*> _objects;

	void addObjects(vector<BreakpointObject*> objects);

	void removeObject(BreakpointObject* objectToRemove);

	void hitObject(BreakpointObject* hitObject);

	void relaunchBall();

public:
	BreakpointController() {
		tinyxml2::XMLDocument params;
		params.LoadFile("Parameters/Parameters.xml");
		tinyxml2::XMLElement* rootElement = params.RootElement();

		int playerWidth = rootElement->FirstChildElement("playerWidth")->IntText();

		_objects.push_back(new Player(0, windowHeight - 50, playerWidth, 15));

		_levelController= LevelController();
		_ball = Ball(windowWidth / 2, windowHeight - 55, 10);

		drawWalls();		
	}

	void drawWalls();

	void deleteObjects();

	// used directly from main.cpp
	void addSoundToQueue(sf::SoundBuffer* buffer);

	Ball getBallInstance();

	void movePlayer(sf::Vector2i coordinates);

	void updateFrame(float dt); 

	vector<sf::RectangleShape> shapesToDraw();
};

