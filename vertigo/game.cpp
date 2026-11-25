#include "game.h"
#include "button.h"
#include <vector>
#include <optional>
#include <cstdlib>
#include <ctime>

void run(sf::RenderWindow& window)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	sf::RectangleShape player({ 40.f, 40.f });
	player.setFillColor(sf::Color::Transparent);
	player.setOutlineThickness(3.0f);
	player.setOutlineColor(mainCl);
	player.setPosition({ 380.f, 500.f });
	int points;
	

	float playerSpeed = 300.f;
	float verticalSpeed = -500.f;
	float gravity = 600.f;
	float jumpForce = -500.f;

	sf::RectangleShape ground({ 800.f, 10.f });
	ground.setPosition({ 0.f, 540.f });
	ground.setFillColor(buttonCl);

	std::vector<sf::RectangleShape> platforms;

	sf::RectangleShape platform1({ 120.f, 15.f });
	platform1.setPosition({ 340.f, 430.f });
	platform1.setFillColor(sf::Color::Transparent);
	platform1.setOutlineThickness(3.0f);
	platform1.setOutlineColor(mainCl);
	platforms.push_back(platform1);

	sf::RectangleShape platform2({ 120.f, 15.f });
	platform2.setPosition({ 180.f, 330.f });
	platform2.setFillColor(sf::Color::Transparent);
	platform2.setOutlineThickness(3.0f);
	platform2.setOutlineColor(mainCl);
	platforms.push_back(platform2);

	sf::RectangleShape platform3({ 120.f, 15.f });
	platform3.setPosition({ 480.f, 230.f });
	platform3.setFillColor(sf::Color::Transparent);
	platform3.setOutlineThickness(3.0f);
	platform3.setOutlineColor(mainCl);
	platforms.push_back(platform3);

	sf::RectangleShape platform4({ 120.f, 15.f });
	platform4.setPosition({ 300.f, 130.f });
	platform4.setFillColor(sf::Color::Transparent);
	platform4.setOutlineThickness(3.0f);
	platform4.setOutlineColor(mainCl);
	platforms.push_back(platform4);

	float nextPlatformY = 30.f;

	sf::View camera = window.getDefaultView();
	float cameraSpeed = 100.f;

	sf::Text gameOverText(mainFont, "GAME OVER", 40);
	gameOverText.setFillColor(mainCl);

	sf::Text menuText(mainFont, "PRESS ENTER TO RETURN", 18);
	menuText.setFillColor(mainCl);

	sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
	gameOverText.setOrigin({gameOverBounds.position.x + gameOverBounds.size.x / 2.f,gameOverBounds.position.y + gameOverBounds.size.y / 2.f});
	gameOverText.setPosition({ 400.f, 250.f });

	sf::FloatRect menuBounds = menuText.getLocalBounds();
	menuText.setOrigin({menuBounds.position.x + menuBounds.size.x / 2.f,menuBounds.position.y + menuBounds.size.y / 2.f});
	menuText.setPosition({ 400.f, 320.f });

	bool gameOver = false;

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
					window.setView(window.getDefaultView());
					return;
				}

				if (gameOver && key->code == sf::Keyboard::Key::Enter)
				{
					window.setView(window.getDefaultView());
					return;
				}
			}
		}

		float deltaTime = clock.restart().asSeconds();

		if (!gameOver)
		{

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			{
				player.move({ -playerSpeed * deltaTime, 0.f });
			}

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

			float previousBottom = player.getPosition().y + player.getSize().y;

			verticalSpeed = verticalSpeed + gravity * deltaTime;

			player.move({ 0.f, verticalSpeed * deltaTime });

			float currentBottom = player.getPosition().y + player.getSize().y;

			if (verticalSpeed > 0.f)
			{
				for (int i = 0; i < platforms.size(); i++)
				{
					float platformX = platforms[i].getPosition().x;
					float platformY = platforms[i].getPosition().y;
					float platformWidth = platforms[i].getSize().x;

					float playerLeft = player.getPosition().x;
					float playerRight = playerLeft + player.getSize().x;

					bool horizontalCollision = playerRight > platformX && playerLeft < platformX + platformWidth;

					bool verticalCollision = previousBottom <= platformY && currentBottom >= platformY;

					if (horizontalCollision && verticalCollision)
					{
						player.setPosition({ player.getPosition().x, platformY - player.getSize().y });
						verticalSpeed = jumpForce;
						break;
					}
				}
			}

			float cameraPosition = camera.getCenter().y;

			if (player.getPosition().y < cameraPosition - cameraSpeed)
			{
				camera.setCenter({ 400.f, player.getPosition().y + cameraSpeed });
			}

			float cameraTop = camera.getCenter().y - window.getSize().y / 2.f;
			float cameraBottom = camera.getCenter().y + window.getSize().y / 2.f;

			while (nextPlatformY > cameraTop - 200.f)
			{
				sf::RectangleShape newPlatform({ 120.f, 15.f });
				float platformX = static_cast<float>(std::rand() % (static_cast<int>(window.getSize().x) - 120));

				newPlatform.setPosition({ platformX, nextPlatformY });
				newPlatform.setFillColor(sf::Color::Transparent);
				newPlatform.setOutlineThickness(3.0f);
				newPlatform.setOutlineColor(mainCl);

				platforms.push_back(newPlatform);

				nextPlatformY -= static_cast<float>(80 + std::rand() % 41);
			}

			for (int i = 0; i < platforms.size();)
			{
				if (platforms[i].getPosition().y > cameraBottom + 200.f)
				{
					platforms.erase(platforms.begin() + i);
				}
				else
				{
					i++;
				}
			}

			if (player.getPosition().y > cameraBottom)
			{
				gameOver = true;
			}
		}

		if (gameOver)
		{
			window.setView(window.getDefaultView());
			window.clear(backgroundCl);
			window.draw(gameOverText);
			window.draw(menuText);
			window.display();
			continue;
		}

		window.setView(camera);
		window.clear(backgroundCl);
		window.draw(ground);

		for (int i = 0; i < platforms.size(); i++)
		{
			window.draw(platforms[i]);
		}

		window.draw(player);
		window.display();
	}

	window.setView(window.getDefaultView());
}
