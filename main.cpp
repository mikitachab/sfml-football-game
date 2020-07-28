#include "VectorUtils.hpp"
#include "Game.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

const auto WIDTH = 800;
const auto HEIGHT = 600;

int main()
{
    sf::RenderWindow window;
    auto game = Game{&window, sf::Vector2u(WIDTH, HEIGHT)};
    game.runGameLoop();
    return 0;
}