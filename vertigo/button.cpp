#include "button.h"

sf::Font mainFont;

bool loadFont()
{
    return mainFont.openFromFile("../res/Minecraft.ttf");
}

Button createButton(float positionX, float positionY, const std::string& text)
{ 
    Button button{ sf::RectangleShape({200.f, 50.f}), sf::Text(mainFont, text, 24) };
    button.button.setPosition({ positionX, positionY });
    button.text.setPosition({ positionX+20.0f, positionY + 10.0f });
    return button;
}

void drawButton(sf::RenderWindow& window, Button& button, bool isSelected)
{
    if (isSelected)
    {
        button.button.setFillColor(mainCl);
        button.text.setFillColor(buttonCl);
    }
    else
    {
        button.button.setFillColor(buttonCl);
        button.text.setFillColor(mainCl);
    }
    window.draw(button.button);
    window.draw(button.text);
}
