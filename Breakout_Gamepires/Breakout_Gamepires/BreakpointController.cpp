#include "BreakpointController.h"

void BreakpointController::addObjects(vector<BreakpointObject*> objects)
{
    _objects.insert(_objects.end(), objects.begin(), objects.end());
    for (BreakpointObject* object : objects) {
        _shapes.push_back(sf::RectangleShape(sf::Vector2f(object->getWidth(), object->getHeight())));
        _shapes.back().setPosition(object->getPosX(), object->getPosY());
        //apply texture
        if (SoftBlock* b = dynamic_cast<SoftBlock*>(object)) {
            /*sf::Texture t;
            if (t.loadFromFile(b->getTexturePath()))
                _shapes.back().setTexture(t);*/
            _shapes.back().setFillColor(sf::Color::White);
        }
        if (MediumBlock* b = dynamic_cast<MediumBlock*>(object)) {
            /*sf::Texture t;
            if (t.loadFromFile(b->getTexturePath()))
                _shapes.back().setTexture(t);*/
            _shapes.back().setFillColor(sf::Color::Green);

        }
        if (HardBlock* b = dynamic_cast<HardBlock*>(object)) {
            /*sf::Texture t;
            if (t.loadFromFile(b->getTexturePath()))
                _shapes.back().setTexture(t);*/
            _shapes.back().setFillColor(sf::Color::Magenta);

        }
        if (ImpenetrableBlock* b = dynamic_cast<ImpenetrableBlock*>(object)) {
            /*sf::Texture t;
            if (t.loadFromFile(b->getTexturePath()))
                _shapes.back().setTexture(t);*/
            _shapes.back().setFillColor(sf::Color::Red);

        }
    }
}

void BreakpointController::removeObject(BreakpointObject* objectToRemove)
{
    _objects.erase(std::remove(_objects.begin(), _objects.end(), objectToRemove));
    for (size_t i = 0; i < _shapes.size(); i++)
        if (_shapes[i].getPosition().x == objectToRemove->getPosX() && _shapes[i].getPosition().y == objectToRemove->getPosY())
            _shapes.erase(_shapes.begin() + i);    
    
    delete objectToRemove;
}

void BreakpointController::hitObject(BreakpointObject* hitObject)
{
    if (Block* b = dynamic_cast<Block*>(hitObject))
        if (b->loseHealth()) {
            //play break sound
            removeObject(hitObject);
        }
    // play hit sound
}

void BreakpointController::relaunchBall()
{
    _ball = Ball(windowWidth / 2, windowHeight - 55, 10);
}

void BreakpointController::updateFrame(float dt)
{
    // ball moving
    _ball.update(dt);
    _ball.setPosition(_ball.getPosX(), _ball.getPosY());

    // collision check
    for (size_t i = 0; i < _objects.size(); i++) {
        int objectEdge = _ball.isInCollision<int>(_objects[i]);
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
            if (i > 3)
                hitObject(_objects[i]);
        }
    }

    // player collision
    int angleOfBounce = _ball.isInCollision<float>(_objects.front());
    if (angleOfBounce != 0.0f)
        _ball.setDirection(angleOfBounce);

    // load new level
    if (_objects.size() < 5) {
        relaunchBall();
        addObjects(_levelController.loadBlocksForNextLevel());
    }
}

vector<sf::RectangleShape> BreakpointController::shapesToDraw()
{
    return _shapes;
}

void BreakpointController::movePlayer(sf::Vector2i coordinates)
{
    _objects.front()->setPosX((float) coordinates.x - _objects.front()->getWidth() / 2);    
    _shapes.front().setPosition(_objects.front()->getPosX(), _shapes.front().getPosition().y);

}

void BreakpointController::addSoundToQueue(sf::SoundBuffer* buffer)
{
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
    /*for (BreakpointObject* obj : _objects)
        delete obj;*/
}
