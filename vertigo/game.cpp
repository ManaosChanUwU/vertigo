#include "game.h"
#include "button.h"

void run(sf::RenderWindow& window)
{
	sf::RectangleShape player({ 40.f, 40.f });
	player.setFillColor(mainCl);
	player.setPosition({ 380.f, 500.f });
	float playerSpeed = 300.f;
	float verticalSpeed = -500.f;
	float gravity = 600.f;
	float jumpForce = -500.f;
	bool isGrounded = false;

	float groundY = 500.f;

	sf::RectangleShape ground({ 800.f, 10.f });
	ground.setPosition({ 0.f, 540.f });
	ground.setFillColor(buttonCl);

	std::vector<sf::RectangleShape> platforms;

	sf::RectangleShape platform1({ 120.f, 15.f });
	platform1.setPosition({ 340.f, 430.f });
	platform1.setFillColor(mainCl);
	platforms.push_back(platform1);

	sf::RectangleShape platform2({ 120.f, 15.f });
	platform2.setPosition({ 180.f, 330.f });
	platform2.setFillColor(mainCl);
	platforms.push_back(platform2);

	sf::RectangleShape platform3({ 120.f, 15.f });
	platform3.setPosition({ 480.f, 230.f });
	platform3.setFillColor(mainCl);
	platforms.push_back(platform3);

	sf::RectangleShape platform4({ 120.f, 15.f });
	platform4.setPosition({ 300.f, 130.f });
	platform4.setFillColor(mainCl);
	platforms.push_back(platform4);

	sf::View camera = window.getDefaultView();
	float cameraSpeed = 100.f;

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
			}
		}

		float deltaTime = clock.restart().asSeconds();

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
					isGrounded = false;

					break;
				}
			}
		}

		if (player.getPosition().y >= groundY)
		{
			player.setPosition({ player.getPosition().x, groundY });

			verticalSpeed = jumpForce;
			isGrounded = false;
		}

		float cameraPosition = camera.getCenter().y;

		if (player.getPosition().y < cameraPosition - cameraSpeed)
		{
			camera.setCenter({ 400.f, player.getPosition().y + cameraSpeed });
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