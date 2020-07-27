#include "VectorUtils.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

const auto TITLE = "SFML Haxball";
const auto WIDTH = 800;
const auto HEIGHT = 600;

const auto WALL_WIDTH = 30;
const auto PLAYER_SIZE = 30;

struct Frame {
    sf::RenderWindow* window;
    float wallWidth;


    auto getWalls(){
        auto windowSize = window->getSize();

        auto topWall = sf::RectangleShape(sf::Vector2f(windowSize.x, wallWidth));

        auto bottomWall = sf::RectangleShape(topWall);
        bottomWall.setPosition(bottomWall.getPosition().x, windowSize.y - wallWidth);

        auto rightWall = sf::RectangleShape(sf::Vector2f(windowSize.y, wallWidth));
        rightWall.setPosition(sf::Vector2f(wallWidth, 0));
        rightWall.rotate(90.0f);

        auto leftWall = sf::RectangleShape(rightWall);
        leftWall.setPosition(sf::Vector2f(windowSize.x, 0));
        
        return std::vector<sf::RectangleShape>{topWall, bottomWall, rightWall, leftWall};
    }


    void draw(){
        for (const auto wall : getWalls()){
            window->draw(wall);
        }
    }
  
};



struct Game {
    sf::RenderWindow* window;
    bool running;
    Frame frame;
    sf::CircleShape player;

    Game(sf::RenderWindow* window) : window(window), running(true) {
        frame = Frame{window, WALL_WIDTH};
        player = sf::CircleShape(PLAYER_SIZE);
        auto center = sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2);
        player.setPosition(sf::Vector2f(center.x - player.getRadius(), center.y - player.getRadius()));
    }

    void UpdateAndDraw(){
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player.move(-0.1f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player.move(0.1f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            player.move(0.0f, -0.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            player.move(0.0f, 0.1f);
        }

        window->clear();
        frame.draw();
        window->draw(player);
        window->display();
    }   

    bool isRunning(){
        return window->isOpen();
    }

    void runGameLoop(){
        while (isRunning()){
            UpdateAndDraw();
        }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), TITLE);
    auto game = Game(&window);
    game.runGameLoop();

    return 0;
}