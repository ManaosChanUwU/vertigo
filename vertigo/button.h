#pragma once
#include <SFML/Graphics.hpp>
#include <string>

struct Button
{
    sf::RectangleShape button;
    sf::Text text;
};

extern sf::Font mainFont;
bool loadFont();
Button createButton(float positionX, float positionY, const std::string& text);
void drawButton(sf::RenderWindow& window, Button& button, bool sellected);

const sf::Color backgroundCl(20u, 20u, 30u);
const sf::Color mainCl(60u, 255u, 120u);
const sf::Color buttonCl(40u, 40u, 60u);
