#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Animation");

    // Define a circle shape for our animated object
    sf::CircleShape circle(50);
    circle.setFillColor(sf::Color::Blue);
    
    // Set initial position
    float x = 100;
    float y = 100;
    circle.setPosition(x, y);

    // Animation loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update position
        x += 0.1; // Adjust the speed as needed
        y += 0.1;
        circle.setPosition(x, y);

        window.clear();
        window.draw(circle);
        window.display();
    }

    return 0;
}
