#include "BreakpointController.h"

void BreakpointController::createPlayer()
{
    _shapes.push_back(sf::RectangleShape(sf::Vector2f(_player.getWidth() - _player.getPosX(),  _player.getHeight() - _player.getPosY())));
    _shapes.back().setPosition(0, PLAYER_VERTICAL_POSITION);
    _shapes.back().setOrigin(50.0f, 0);
}

void BreakpointController::Initialize()
{
}

LevelInitializer BreakpointController::getLevelInitializer()
{
    return _levelInitializer;
}

void BreakpointController::updateFrame(float dt)
{
    // player moving
    _shapes.front().setPosition(_player.getPosX(), _shapes.front().getPosition().y);

    // ball moving
    float deltaX, deltaY;
    _ball.getDirections(deltaX, deltaY);
    _ball.setPosition(_ball.getPosX() + deltaX * 60 * dt, _ball.getPosY() + deltaY * 60 * dt);

    // collision check
    for (BreakpointObject* object : _objects) {
        if (_ball.isInCollision(object)) {
            _ball.setDirection(270);
        }
    }
}

vector<sf::RectangleShape> BreakpointController::shapesToDraw()
{
    return _shapes;
}

void BreakpointController::movePlayer(sf::Vector2i coordinates)
{
    _player.setPosX((float) coordinates.x);
}

Ball BreakpointController::getBallInstance()
{
    return _ball;
}

void BreakpointController::drawWalls()
{
    _objects.push_back(new Wall(0, 0, 1600, 10));
    _objects.push_back(new Wall(1590, 0, 10, 900));
    _objects.push_back(new Wall(0, 0, 10, 900));

    for (BreakpointObject* wall : _objects) {
        _shapes.push_back(sf::RectangleShape(sf::Vector2f(wall->getWidth(), wall->getHeight())));
    }
    for (size_t i = 1; i < _shapes.size(); i++) {
        _shapes[i].setPosition(_objects[i-1]->getPosX(), _objects[i-1]->getPosY());
        _shapes[i].setFillColor(sf::Color::Red);
    }
    
}

void BreakpointController::deleteObjects()
{
    for (BreakpointObject* obj : _objects)
        delete obj;
}
