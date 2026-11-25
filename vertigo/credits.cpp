#include "credits.h"
#include "button.h"

void credits(sf::RenderWindow& window)
{
	sf::Text title(mainFont, "CREDITOS", 40);
	title.setPosition({ 270.f, 100.f });
	title.setFillColor(mainCl);

	sf::Text gameName(mainFont, "VERTIGO", 28);
	gameName.setPosition({ 300.f, 220.f });
	gameName.setFillColor(mainCl);

	sf::Text developer(mainFont, "Desarrollado por:", 20);
	developer.setPosition({ 250.f, 300.f });
	developer.setFillColor(mainCl);

	sf::Text author(mainFont, "ManaosChanUwU", 24);
	author.setPosition({ 260.f, 350.f });
	author.setFillColor(mainCl);

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

			const sf::Event::KeyPressed* key = event->getIf<sf::Event::KeyPressed>();

			if (key != nullptr)
			{
				if (key->code == sf::Keyboard::Key::Escape || key->code == sf::Keyboard::Key::Enter)
				{
					return;
				}
			}
		}

		window.clear(backgroundCl);
		window.draw(title);
		window.draw(gameName);
		window.draw(developer);
		window.draw(author);
		window.draw(back);
		window.display();
	}
}