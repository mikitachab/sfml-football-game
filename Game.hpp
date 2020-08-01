#include "Frame.hpp"
#include "InputMap.hpp"

#include <SFML/Graphics.hpp>


#include <iostream>


const auto TITLE = "SFML Haxball";
const auto PLAYER_SIZE = 30;


struct Game {
    sf::RenderWindow* window;
    sf::Vector2u windowSize;
    Frame frame;

    sf::CircleShape player;
    float moveSpeed{0.1};

    Game(sf::RenderWindow* window, sf::Vector2u windowSize) : window(window), windowSize(windowSize){
        window->create(sf::VideoMode(windowSize.x, windowSize.y), TITLE);
        initScene();
    }

    void initScene(){
        frame = Frame{window};
        player = sf::CircleShape(PLAYER_SIZE);
        auto center = sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2);
        player.setPosition(sf::Vector2f(center.x - player.getRadius(), center.y - player.getRadius()));
    }

    void handleWindowEvents(){
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window->close();
                break;
            default:
                break;
            }
        }
    }

    bool isPlayerCollidingWithWalls(){
        for (const auto wall : frame.walls){
            if (player.getGlobalBounds().intersects(wall.getGlobalBounds())){
                return true;
            } 
        }
        return false;
    }

    void handleInput(){
        sf::Vector2f moveVector = getMoveVector();
        sf::Vector2f oldPosition = player.getPosition();
        player.move(moveVector);
        if (isPlayerCollidingWithWalls()) {
            player.setPosition(oldPosition);
        }
    }

    sf::Vector2f getMoveVector(){
        float x = 0;
        float y = 0;
        
        if (InputMap::left())
        {   
            x -= moveSpeed;
        }
        if (InputMap::right())
        {
            x += moveSpeed;  
        }
        if (InputMap::up())
        {
            y -= moveSpeed;
        }
        if (InputMap::down())
        {
            y += moveSpeed;
        }
        return sf::Vector2f(x,y);
    }

    void UpdateAndDraw(){
        Update();
        Draw();
    }

    void Update(){
        handleWindowEvents();
        handleInput();
    }

    void Draw(){
        window->clear();
        window->draw(frame);
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