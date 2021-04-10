#include "BreakpointController.h"

void BreakpointController::addObjects(vector<BreakpointObject*> objects)
{
    _objects.insert(_objects.end(), objects.begin(), objects.end());
    for (BreakpointObject* object : objects) {
        _shapes.push_back(sf::RectangleShape(sf::Vector2f(object->getWidth(), object->getHeight())));
        _shapes.back().setPosition(object->getPosX(), object->getPosY());
    }
}

void BreakpointController::updateFrame(float dt)
{
    // player moving
    _shapes.front().setPosition(_objects.front()->getPosX(), _shapes.front().getPosition().y);

    // ball moving
    float deltaX, deltaY;
    _ball.getDirections(deltaX, deltaY);
    _ball.setPosition(_ball.getPosX() + deltaX * dt * _ball.getSpeed(), _ball.getPosY() + deltaY * dt * _ball.getSpeed());
    _ball.setPosition(_ball.getPosX(), _ball.getPosY());

    // collision check
    for (BreakpointObject* object : _objects) {
        int objectEdge = _ball.isInCollision<int>(object);
        if (objectEdge != 0) {
            switch (objectEdge) {
            case 1:
            case 3:
                _ball.invertDirectionVector("y");
                break;
            case 2:
            case 4:
                _ball.invertDirectionVector("x");
                break;
            default:
                _ball.setDirection(_ball.getDirectionAngle() + 180);
            }
        }
    }

    int angleOfBounce = _ball.isInCollision<float>(_objects.front());
    if (angleOfBounce != 0.0f)
        _ball.setDirection(angleOfBounce);
}

vector<sf::RectangleShape> BreakpointController::shapesToDraw()
{
    return _shapes;
}

void BreakpointController::movePlayer(sf::Vector2i coordinates)
{
    _objects.front()->setPosX((float) coordinates.x - _objects.front()->getWidth() / 2);
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

    for (BreakpointObject* object : _objects) {
        _shapes.push_back(sf::RectangleShape(sf::Vector2f(object->getWidth(), object->getHeight())));
    }

    for (size_t i = 0; i < _shapes.size(); i++) {
        _shapes[i].setPosition(_objects[i]->getPosX(), _objects[i]->getPosY());
        if (i != 0)
            _shapes[i].setFillColor(sf::Color::Red);
    }
    
    addObjects(_levelController.loadBlocksForNextLevel());
}

void BreakpointController::deleteObjects()
{
    for (BreakpointObject* obj : _objects)
        delete obj;
}
