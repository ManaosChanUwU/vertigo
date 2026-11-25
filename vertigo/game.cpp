#include "game.h"
#include "button.h"
#include <optional>

void run(sf::RenderWindow& window)
{
	sf::RectangleShape player({ 40.f, 40.f });
	player.setFillColor(mainCl);
	player.setPosition({ 380.f, 500.f });
	float playerSpeed = 300.f;

	sf::Clock clock;

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

		float deltaTime = clock.restart().asSeconds();

		//izqioerda
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			player.move({ -playerSpeed * deltaTime, 0.f });
		}

		//derecha
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			player.move({ playerSpeed * deltaTime, 0.f });
		}

		
		if (player.getPosition().x < 0.f)
		{
			player.setPosition({ 0.f, player.getPosition().y });
		}

		float rightLimit = window.getSize().x - player.getSize().x;
		if (player.getPosition().x > rightLimit)
		{
			player.setPosition({ rightLimit, player.getPosition().y });
		}

		// Dibujar
		window.clear(backgroundCl);
		window.draw(player);
		window.display();
	}
}
