#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include <iostream>
#include "Ball.h"
#include "BreakpointController.h"

using namespace tinyxml2;
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Breakpoint");

    BreakpointController gameController = BreakpointController();

    vector<Level> levels = gameController.getLevelInitializer().getLevels();

    sf::CircleShape ball(5.0f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                gameController.movePlayer(mousePosition);
            }
        }

        gameController.updateFrame();

        ball.setPosition(gameController.getBallInstance().getPosX(), gameController.getBallInstance().getPosY());

        window.clear();

        for (sf::RectangleShape shape : gameController.shapesToDraw())
        {
            window.draw(shape);
        }
        window.draw(ball);

        window.display();
    }

    return 0;
}