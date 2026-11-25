#include "menu.h"
#include "button.h"
#include "howToPlay.h"
#include "credits.h"
#include "game.h"

void run()
{
    if (!loadFont())
    {
        return;
    }

    sf::RenderWindow window(sf::VideoMode({ 800u, 600u }), "VERTIGO");

    // Titulo
    sf::Text title(mainFont, "VERTIGO", 60);
    title.setPosition({ 240.f, 60.f });
    title.setFillColor(mainCl);

    // Botones
    Button buttonPlay = createButton(300.f, 200.f, "Jugar");
    Button buttonHowToPlay = createButton(300.f, 280.f, "Instrucciones");
    Button buttonCredits = createButton(300.f, 360.f, "Creditos");
    Button buttonExit = createButton(300.f, 440.f, "Salir");

    int selectedOption = 0;
    const int optionQuantity = 4;

    while (window.isOpen())
    {
        while (std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                return;
            }

            const sf::Event::KeyPressed* key =
                event->getIf<sf::Event::KeyPressed>();

            if (key != nullptr)
            {
                if (key->code == sf::Keyboard::Key::Down)
                {
                    if (selectedOption < optionQuantity - 1)
                    {
                        selectedOption++;
                    }
                    else
                    {
                        selectedOption = 0;
                    }
                }

                if (key->code == sf::Keyboard::Key::Up)
                {
                    if (selectedOption > 0)
                    {
                        selectedOption--;
                    }
                    else
                    {
                        selectedOption = optionQuantity - 1;
                    }
                }

                if (key->code == sf::Keyboard::Key::Enter)
                {
                    if (selectedOption == 0)
                    {
                        run(window);
                    }
                    else if (selectedOption == 1)
                    {
                        howToPlay(window);
                    }
                    else if (selectedOption == 2)
                    {
                        credits(window);
                    }
                    else if (selectedOption == 3)
                    {
                        window.close();
                    }
                }
            }
        }

        window.clear(backgroundCl);

        window.draw(title);

        drawButton(window, buttonPlay, selectedOption == 0);
        drawButton(window, buttonHowToPlay, selectedOption == 1);
        drawButton(window, buttonCredits, selectedOption == 2);
        drawButton(window, buttonExit, selectedOption == 3);

        window.display();
    }
}