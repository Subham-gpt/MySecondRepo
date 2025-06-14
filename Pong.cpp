#include "Bat.h"
#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

int main()
{
    // VideoMode Object
    VideoMode vm(1366, 768);
    // Create a window
    RenderWindow window(vm, "Pong", Style::Fullscreen);

    // Create the Bat
    Bat bat(1366 / 2.0, 768 - 20);
    // Create the Ball
    Ball ball(1366 / 2.0,0);

    // Create HUD(Heads Up Display)
    Text hud;
    Font font;
    font.loadFromFile("DS-DIGI.TTF");
    hud.setFont(font);
    hud.setCharacterSize(75);
    hud.setFillColor(Color::White);
    hud.setString("Score : 0    Lives : 3");
    hud.setPosition(20, 20);

    // Initialized Score & Time
    int score = 0;
    int lives = 3;

    // Manage Time
    Clock clock;

    // Main Loop
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        // Handle Quitting Events
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }
        // Handle the Right Cursor
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            if (bat.get_Position().left + bat.get_Position().width > 1366)
            {
                bat.stopRight();
            }
            else
            {
                bat.moveRight();
            }
        }
        else
        {
            bat.stopRight();
        }

        // Handle the Left Cursor
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            if (bat.get_Position().left < 0)
            {
                bat.stopLeft();
            }
            else
            {
                bat.moveLeft();
            }
        }
        else
        {
            bat.stopLeft();
        }

        // Update time
        Time dt = clock.restart();

        // Update bat
        bat.update(dt);

        // Update ball
        ball.update(dt);

        // Update Score
        std::stringstream ss;
        ss << "Score: " << score << "  Lives: " << lives;
        hud.setString(ss.str());

        // Ball hitting the bottom
        if (ball.get_Position().top > window.getSize().y) {
            // Reverse the ball direction
            ball.reboundBottom();
            // Lives reduce
            lives--;
            if(lives<1) {
                // Reset score
                score = 0;
                // Reset lives
                lives = 3;
            }
        }
        // Ball hitting the top
        if (ball.get_Position().top < 0) {
            // Add score
            score++;
            ball.reboundBatOrTop();
        }

        // Ball hitting the sides
        if (ball.get_Position().left < 0 || ball.get_Position().left+10 > window.getSize().x) {
            ball.reboundSides();
        }

        // Ball hitting the bat
        if (ball.get_Position().intersects(bat.get_Position())) {
            // Hit detected, so reverse the ball and increase the score
            ball.reboundBatOrTop();
            score++;
        }

        // Display
        window.clear();
        window.draw(hud);
        window.draw(bat.get_Shape());
        window.draw(ball.get_Shape());
        window.display();
    }
    return 0;
}
