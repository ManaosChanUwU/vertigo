#include "howToPlay.h"
#include "button.h"

void howToPlay(sf::RenderWindow& window)
{
    sf::Text title(mainFont, "INSTRUCCIONES", 40);
    title.setPosition({ 180.f, 70.f });
    title.setFillColor(mainCl);

    sf::Text movement(mainFont, "Moverse: A / D o Flechas", 22);
    movement.setPosition({ 170.f, 200.f });
    movement.setFillColor(mainCl);

    sf::Text jump(mainFont, "El personaje salta automaticamente", 22);
    jump.setPosition({ 100.f, 260.f });
    jump.setFillColor(mainCl);

    sf::Text platforms(mainFont, "Salta sobre las plataformas", 22);
    platforms.setPosition({ 160.f, 320.f });
    platforms.setFillColor(mainCl);

    sf::Text objective(mainFont, "Llega lo mas alto posible", 22);
    objective.setPosition({ 160.f, 380.f });
    objective.setFillColor(mainCl);

    sf::Text back(mainFont, "ESC / ENTER - VOLVER", 18);
    back.setPosition({ 230.f, 500.f });
    back.setFillColor(mainCl);

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
                if (key->code == sf::Keyboard::Key::Escape ||
                    key->code == sf::Keyboard::Key::Enter)
                {
                    return;
                }
            }
        }

        window.clear(backgroundCl);

        window.draw(title);
        window.draw(movement);
        window.draw(jump);
        window.draw(platforms);
        window.draw(objective);
        window.draw(back);

        window.display();
    }
}