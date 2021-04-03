#include "BreakpointController.h"

void BreakpointController::createPlayer()
{
    _shapes.push_back(sf::RectangleShape(sf::Vector2f(_player.getEndX() - _player.getPosX(),  _player.getEndY() - _player.getPosY())));
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

void BreakpointController::updateFrame()
{
    _shapes[0].setPosition(_player.getPosX(), _shapes[0].getPosition().y);

    float deltaX, deltaY;
    _ball.getDirections(deltaX, deltaY);
    _ball.setPosition(_ball.getPosX() + deltaX, _ball.getPosY() + deltaY);
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
