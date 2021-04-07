#pragma once
#include "LevelInitializer.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Block.h"

#define PLAYER_VERTICAL_POSITION 850

class BreakpointController
{
private:
	LevelInitializer _levelInitializer;
	Player _player;
	vector<sf::RectangleShape> _shapes;
	Ball _ball;
	vector<BreakpointObject*> _objects;

public:
	BreakpointController() {
		tinyxml2::XMLDocument params;
		params.LoadFile("Params/Parameters.xml");
		tinyxml2::XMLElement* rootElement = params.RootElement();

		int playerWidth = rootElement->FirstChildElement("playerWidth")->IntText();
		_player = Player(0, PLAYER_VERTICAL_POSITION, playerWidth, PLAYER_VERTICAL_POSITION + 15);

		_levelInitializer = LevelInitializer();
		_ball = Ball(800, PLAYER_VERTICAL_POSITION + 5, 10);
		createPlayer();

		drawWalls();
	}

	void createPlayer();

	void Initialize();

	LevelInitializer getLevelInitializer();

	void updateFrame(float dt); 

	vector<sf::RectangleShape> shapesToDraw();

	void movePlayer(sf::Vector2i coordinates);

	Ball getBallInstance();

	void drawWalls();

	void deleteObjects();









	void addSoundToQueue(sf::SoundBuffer* buffer);
};

