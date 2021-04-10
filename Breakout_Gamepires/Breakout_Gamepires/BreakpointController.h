#pragma once
#include "Level.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "LevelController.h"

#define PLAYER_VERTICAL_POSITION 850

class BreakpointController
{
private:
	Ball _ball;
	vector<sf::RectangleShape> _shapes;
	vector<BreakpointObject*> _objects;
	LevelController _levelController;

	void addObjects(vector<BreakpointObject*> objects);

public:
	BreakpointController() {
		tinyxml2::XMLDocument params;
		params.LoadFile("Parameters/Parameters.xml");
		tinyxml2::XMLElement* rootElement = params.RootElement();

		int playerWidth = rootElement->FirstChildElement("playerWidth")->IntText();

		_objects.push_back(new Player(0, PLAYER_VERTICAL_POSITION, playerWidth, 15));

		_levelController= LevelController();
		_ball = Ball(800, PLAYER_VERTICAL_POSITION + 5, 10);

		drawWalls();		
	}

	void createPlayer();

	void drawWalls();

	void deleteObjects();

	// used directly from main.cpp
	void addSoundToQueue(sf::SoundBuffer* buffer);

	Ball getBallInstance();

	void movePlayer(sf::Vector2i coordinates);

	void updateFrame(float dt); 

	vector<sf::RectangleShape> shapesToDraw();
};

