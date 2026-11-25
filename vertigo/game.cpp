#include "game.h"
#include "button.h"

void run(sf::RenderWindow& window)
{
	sf::Text title(mainFont, "VERTIGO", 50);
	title.setPosition({ 270.f, 100.f });
	title.setFillColor(mainCl);

	sf::Text message(mainFont, "EL JUEGO COMIENZA AQUI", 22);
	message.setPosition({ 140.f, 270.f });
	message.setFillColor(mainCl);

	sf::Text back(mainFont, "ESC - VOLVER AL MENU", 18);
	back.setPosition({ 220.f, 500.f });
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

			const sf::Event::KeyPressed* key = event->getIf<sf::Event::KeyPressed>();

			if (key != nullptr)
			{
				if (key->code == sf::Keyboard::Key::Escape)
				{
					return;
				}
			}
		}
		window.clear(backgroundCl);
		window.draw(title);
		window.draw(message);
		window.draw(back);
		window.display();
	}
}