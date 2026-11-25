
#include "game.h"
#include "button.h"

void run(sf::RenderWindow& window)
{
    sf::RectangleShape player({ 40.f, 40.f });
    player.setFillColor(mainCl);
    player.setPosition({ 380.f, 500.f });

    float playerSpeed = 300.f;

    // SALTO Y GRAVEDAD
    float verticalSpeed = 0.f;
    float gravity = 1000.f;
    float jumpForce = -500.f;
    bool isGrounded = true;

    // SUELO
    float groundY = 500.f;

    sf::RectangleShape ground({ 800.f, 10.f });
    ground.setPosition({ 0.f, 540.f });
    ground.setFillColor(buttonCl);

    // PLATAFORMAS
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

    // RELOJ
    sf::Clock clock;

    while (window.isOpen())
    {
        // EVENTOS
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
                if (key->code == sf::Keyboard::Key::Escape)
                {
                    return;
                }

                // SALTAR
                if (isGrounded &&
                    (key->code == sf::Keyboard::Key::Space ||
                        key->code == sf::Keyboard::Key::W ||
                        key->code == sf::Keyboard::Key::Up))
                {
                    verticalSpeed = jumpForce;
                    isGrounded = false;
                }
            }
        }

        // TIEMPO ENTRE FOTOGRAMAS
        float deltaTime = clock.restart().asSeconds();

        // MOVIMIENTO HORIZONTAL
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            player.move({ -playerSpeed * deltaTime, 0.f });
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            player.move({ playerSpeed * deltaTime, 0.f });
        }

        // LIMITES LATERALES
        if (player.getPosition().x < 0.f)
        {
            player.setPosition({ 0.f, player.getPosition().y });
        }

        float rightLimit = window.getSize().x - player.getSize().x;

        if (player.getPosition().x > rightLimit)
        {
            player.setPosition({ rightLimit, player.getPosition().y });
        }

        // MOVIMIENTO VERTICAL Y COLISIONES
        if (!isGrounded)
        {
            // Guardar la posicion inferior anterior del jugador
            float previousBottom =
                player.getPosition().y + player.getSize().y;

            // Aplicar gravedad
            verticalSpeed = verticalSpeed + gravity * deltaTime;

            // Mover jugador verticalmente
            player.move({ 0.f, verticalSpeed * deltaTime });

            float currentBottom =
                player.getPosition().y + player.getSize().y;

            // COLISION CON PLATAFORMAS
            if (verticalSpeed > 0.f)
            {
                for (int i = 0; i < platforms.size(); i++)
                {
                    float platformX = platforms[i].getPosition().x;
                    float platformY = platforms[i].getPosition().y;
                    float platformWidth = platforms[i].getSize().x;

                    float playerLeft = player.getPosition().x;
                    float playerRight =
                        playerLeft + player.getSize().x;

                    // Comprobar si se superponen horizontalmente
                    bool horizontalCollision =
                        playerRight > platformX &&
                        playerLeft < platformX + platformWidth;

                    // Comprobar si el jugador esta cayendo
                    // sobre la plataforma
                    bool verticalCollision =
                        previousBottom <= platformY &&
                        currentBottom >= platformY;

                    if (horizontalCollision && verticalCollision)
                    {
                        // Colocar al jugador encima
                        player.setPosition({
                            player.getPosition().x,
                            platformY - player.getSize().y
                            });

                        verticalSpeed = 0.f;
                        isGrounded = true;

                        break;
                    }
                }
            }

            // COLISION CON EL SUELO
            if (player.getPosition().y >= groundY)
            {
                player.setPosition({
                    player.getPosition().x,
                    groundY
                    });

                verticalSpeed = 0.f;
                isGrounded = true;
            }
        }

        // DIBUJAR
        window.clear(backgroundCl);

        window.draw(ground);

        for (int i = 0; i < platforms.size(); i++)
        {
            window.draw(platforms[i]);
        }

        window.draw(player);

        window.display();
    }
}