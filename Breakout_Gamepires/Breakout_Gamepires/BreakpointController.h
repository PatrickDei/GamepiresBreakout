#pragma once
#include "Level.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "LevelController.h"
#include <algorithm>
#include <SFML/System.hpp>
#include <queue>
#include "TextureController.h"


class BreakpointController
{
private:
	Ball _ball;	
	LevelController _levelController;
	vector<sf::RectangleShape> _shapes;
	vector<BreakpointObject*> _objects;
	bool _gameIsOver;
	int _score;
	const char* _tempSoundPath;
	TextureController _textureController;

	void addObjects(vector<BreakpointObject*> objects);

	void removeObject(BreakpointObject* objectToRemove);

	void hitObject(BreakpointObject* hitObject);

	void relaunchBall();

	bool isGameOver();

	void endTheGame();

	int indestructableBlocks();

public:	
	bool _soundShouldBePlayed;

	int getCurrentScore();

	BreakpointController() : _gameIsOver(false), _soundShouldBePlayed(false), _score(0) {
		tinyxml2::XMLDocument params;
		params.LoadFile("Parameters/Parameters.xml");
		tinyxml2::XMLElement* rootElement = params.RootElement();

		int playerWidth = rootElement->FirstChildElement("playerWidth")->IntText();

		_objects.push_back(new Player(0, windowHeight - 50, playerWidth, 15));

		_levelController= LevelController();
		_ball = Ball(windowWidth / 2, windowHeight - 55, 10);

		drawWalls();		

		_textureController = TextureController();
	}

	void drawWalls();

	int getHealth();

	// used directly from main.cpp
	void addSoundToQueue(sf::SoundBuffer* buffer);

	Ball getBallInstance();

	void movePlayer(sf::Vector2i coordinates);

	void updateFrame(float dt); 

	std::vector<sf::RectangleShape> shapesToDraw();

	bool getGameOver() {
		return _gameIsOver;
	}
};

