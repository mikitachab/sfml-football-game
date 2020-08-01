
#include "VectorUtils.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>


struct Frame: public sf::Drawable {
    sf::RenderWindow* window;
    std::vector<sf::RectangleShape> walls;

    Frame(sf::RenderWindow* window): window(window){
        walls = initWalls();
    }
    
    Frame(){}

    std::vector<sf::RectangleShape> initWalls(){
        auto windowSize = window->getSize();
        float wallWidth = windowSize.x / 100 * 5;
        std::cout << "ww " << wallWidth << std::endl;
        std::cout << "getWalls " << windowSize.x << " " << windowSize.y << std::endl;

        auto topWall = sf::RectangleShape(sf::Vector2f(windowSize.x, wallWidth));

        auto bottomWall = sf::RectangleShape(topWall);
        bottomWall.setPosition(bottomWall.getPosition().x, windowSize.y - wallWidth);

        auto leftWall = sf::RectangleShape(sf::Vector2f(windowSize.y, wallWidth));
        leftWall.setPosition(sf::Vector2f(wallWidth, 0));
        leftWall.rotate(90.0f);

        auto rightWall = sf::RectangleShape(leftWall);
        rightWall.setPosition(sf::Vector2f(windowSize.x, 0));
        auto rp = rightWall.getPosition();
        std::cout << "rw pos";
        vecutils::printVector<decltype(rp)>(rp);
        
        return std::vector<sf::RectangleShape>{topWall, bottomWall, rightWall, leftWall};
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (const auto wall : walls) {
            target.draw(wall, states);
        }
    }
};
