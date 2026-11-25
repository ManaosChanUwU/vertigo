
#include "game.h"
#include "button.h"
#include <optional>

void run(sf::RenderWindow& window)
{
    // Jugador
    sf::RectangleShape player({ 40.f, 40.f });
    player.setFillColor(mainCl);
    player.setPosition({ 380.f, 500.f });

    // Movimiento horizontal
    float playerSpeed = 300.f;

    // Salto y gravedad
    float verticalSpeed = 0.f;
    float gravity = 1000.f;
    float jumpForce = -500.f;
    bool isGrounded = true;

    // Suelo
    float groundY = 500.f;

    // Reloj
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

            const sf::Event::KeyPressed* key =
                event->getIf<sf::Event::KeyPressed>();

            if (key != nullptr)
            {
                if (key->code == sf::Keyboard::Key::Escape)
                {
                    return;
                }

                // Saltar si esta en el suelo
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

        // Tiempo entre fotogramas
        float deltaTime = clock.restart().asSeconds();

        // Movimiento hacia la izquierda
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            player.move({ -playerSpeed * deltaTime, 0.f });
        }

        // Movimiento hacia la derecha
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            player.move({ playerSpeed * deltaTime, 0.f });
        }

        // Aplicar gravedad
        verticalSpeed = verticalSpeed + gravity * deltaTime;

        // Movimiento vertical
        player.move({ 0.f, verticalSpeed * deltaTime });

        // Comprobar contacto con el suelo
        if (player.getPosition().y >= groundY)
        {
            player.setPosition({ player.getPosition().x, groundY });
            verticalSpeed = 0.f;
            isGrounded = true;
        }

        // Limite izquierdo
        if (player.getPosition().x < 0.f)
        {
            player.setPosition({ 0.f, player.getPosition().y });
        }

        // Limite derecho
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
