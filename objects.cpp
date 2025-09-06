// I neeed to commentt this more and also my keyboard sucks f this keyboard

//breaks when you full screen it cause duh
#ifndef circle_H
#define circle_H
#include <thread>    // For threading
#include <vector>
#include <unordered_set>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <cmath>
int const density = 5;
using vecf = sf::Vector2f;

float const pi = 3.14;

float dotProduct(const vecf& vec1, const vecf& vec2) {
    return vec1.x * vec2.x + vec1.y * vec2.y;
}
vecf subtract(const vecf& vec1, const vecf& vec2) {
    return vecf(vec1.x-vec2.x,vec1.y-vec2.y);
}
vecf normalize(const vecf& vec) {
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    if (length != 0.0f) {
        return vecf(vec.x / length, vec.y / length);
    }
    return vecf(0.0f, 0.0f); // Return a zero vector if the length is zero
}
vecf add(const vecf& vec1, const vecf& vec2)  {
    return vecf(vec1.x+vec2.x,vec1.y+vec2.y);
}
vecf scale(const vecf& vec1, float scalar) {
    return vecf(vec1.x*scalar, vec1.y*scalar);
}
class Circle
{ private:
	vecf force;
    vecf velocity;
	vecf acceleration;
    sf::CircleShape shape;
	vecf position;

    float radius;
public:
 Circle(float radius, vecf velo, vecf position, sf::Color color):
    force(0,0),
    acceleration(0,0),
    velocity(velo), position(position),
    radius(radius){
    shape.setFillColor(color);
    shape.setRadius(radius);
    shape.setPosition(position);
    }
    void update(float deltaTime,sf::RenderWindow& window) {
        position = shape.getPosition();
        acceleration=force;
     if (check_wall(window)) {
         velocity.x = -velocity.x;
         acceleration.x = 0;
     }

        if (check_floor_and_ceiling(window)) {
            velocity.y = -velocity.y;
            // velocity.x *=.9* velocity.x;
            acceleration.y = 0;
        }


        vecf final_velocity(0, 0);
        final_velocity.y = velocity.y + acceleration.y * deltaTime;
        final_velocity.x = velocity.x + acceleration.x * deltaTime;

        // Update position using the distance formula
        shape.setPosition(position.x + 0.5f * (velocity.x + final_velocity.x) * deltaTime,
                           position.y + 0.5f * (velocity.y + final_velocity.y) * deltaTime);
        set_manual_velo(final_velocity);
    }
    // Imma do this later
    bool checkcollosions( Circle& circle) {
        vecf other_position = circle.getPosition();

        float dist = (position.x - other_position.x) * (position.x - other_position.x) +
             (position.y - other_position.y) * (position.y - other_position.y);
        dist = std::sqrt(dist);
        if (dist > radius + circle.getradius())
           { return false;}
        else
            {return true;}
    }
    bool check_floor_and_ceiling(sf::RenderWindow& window) {

        unsigned int max = window.getSize().y-70;

        if (max-shape.getPosition().y<radius && velocity.y>0) {
            shape.setPosition(shape.getPosition().x,max-radius);
        return true;

        }


        else if (shape.getPosition().y-radius<0 && velocity.y<0)
        {
            return true;
        }
       return false;
    }
    bool check_wall(sf::RenderWindow& window) {
     if (shape.getPosition().x<-100) {
         return false;
     }

     unsigned int max = window.getSize().x;

     if (max-shape.getPosition().x-30<radius && velocity.x>0) {
         shape.setPosition(max-radius-30,shape.getPosition().y);
         return true;

     }


     else if (shape.getPosition().x-radius<-60 && velocity.x<0)
     {
         return true;
     }
     return false;
 }
    vecf getPosition() const {
        return position;

    }
    void setposition(vecf new_position) {
	position = new_position;
	shape.setPosition(position);
    }
    float getradius() const {
         return radius;
    }
    void set_manual_velo(vecf velo) {
        velocity = velo;

    }
void handle_collision(Circle& circle) {
    // Increment the collision count

    // Calculate the direction vector between the two circles
    vecf direction = subtract(circle.getPosition(), getPosition());
    float direction_length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // Check if there's a collision
    if (direction_length == 0.0f || direction_length > radius + circle.getradius()) {
        return; // No collision
    }

    // Normalize the direction vector
    direction = normalize(direction);

    // Calculate the correction factor to adjust positions
    float corr = (radius + circle.getradius() - direction_length) / 2.0f;

    // Update positions to prevent overlap
    setposition(scale(add(getPosition(), scale(direction, -corr)),1.001));
    circle.setposition(scale(add(circle.getPosition(), scale(direction, corr)),1.001));

    // Calculate the dot products of velocities along the direction vector
    float v1 = dotProduct(direction, velocity);
    float v2 = dotProduct(direction, circle.getVelocity());

    // Assuming the radius represents mass (adjust if you have separate mass variables)
    float m1 = radius;
    float m2 = circle.getradius();

    // Coefficient of restitution (elasticity of the collision)
    float restitution = 1.0f;

    // Calculate the new velocities after collision using the momentum and restitution
    float newV1 = (m1 * v1 + m2 * v2 - m2 * (v1 - v2) * restitution) / (m1 + m2);
    float newV2 = (m1 * v1 + m2 * v2 - m1 * (v2 - v1) * restitution) / (m1 + m2);

    // Update the velocities of both circles
    velocity = add(scale(direction, newV1 - v1), velocity);
    circle.set_manual_velo(add(scale(direction, newV2 - v2), circle.getVelocity()));

    // Debugging output every 100 collisions
}

    void Push_constant_force(vecf FORCE) {
        force += FORCE;

    }
    void setup(sf::RenderWindow& window) const {
     window.draw(shape);
    }
    vecf getVelocity() const {
    return velocity;
    }
    void setcolor() {
    shape.setFillColor(sf::Color::Yellow);
    }

};

void mouse_movement(vecf other_position,std::vector<Circle>& circles){
   Circle* pick = &circles[0];
   vecf position= circles[0].getPosition();
    float dist = (position.x - other_position.x) * (position.x - other_position.x) +
               (position.y - other_position.y) * (position.y - other_position.y);

    for (auto& circle: circles) {
        position = circle.getPosition();
        float other_dist = (position.x - other_position.x) * (position.x - other_position.x) +
               (position.y - other_position.y) * (position.y - other_position.y);
        if ( other_dist < dist) {
        pick = &circle;
        dist = other_dist;
                                }


                    }

    pick->set_manual_velo(vecf(pick->getVelocity().x*1.001,pick->getVelocity().y*1.001));
    pick->setcolor();
}

void createCircles(std::vector<Circle>& circles) {
    int feels{0};
   if (feels==0) {
    // Define a common velocity for all circles
    sf::Vector2f commonVelocity(1000.0f, 0.0f); // You can adjust this speed as needed

    // Create 5 circles with different positions but the same velocity
    for (int i = 0; i < 5000; ++i) {
        // Calculate a different starting position for each circle
        sf::Vector2f position(i * .01* 200.0f, i *.01* 100.0f); // Adjust spacing as needed

        // Create the circle with the same velocity but different position
        circles.emplace_back(10.0f, commonVelocity, position, sf::Color::Blue);
    }
}
   else {

    std::cout<<"yo"<<"/n";
     circles.emplace_back(50, vecf(750, 0), vecf(0, 500), sf::Color::White);
    circles.emplace_back(50, vecf(0, 750), vecf(500, 0), sf::Color::Red);
    }
}

void updateCirclesPhysics(std::vector<Circle>& circles, int start, int end, float deltaTime, sf::RenderWindow& window) {
    for (int i = start; i < end; ++i) {
        circles[i].update(deltaTime, window);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML Animation");
    std::vector<Circle> circles;

    createCircles(circles);

    sf::Clock clock;  // Create a clock to measure time


    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();  // Calculate delta time

        // Handle mouse input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(); 
            sf::Vector2f mousePositionFloat = static_cast<sf::Vector2f>(mousePosition);
            mouse_movement(mousePositionFloat, circles);
        }

        // Handle collisions 
        std::unordered_set<int> collided_circle;
        for (int i = 0; i < circles.size() - 1; ++i) {
            if (collided_circle.find(i) != collided_circle.end()) {
                continue;  // Skip this circle if it has already collided
            }
            for (int j = i + 1; j < circles.size(); ++j) {
                if (circles[i].checkcollosions(circles[j])) {
                    circles[i].handle_collision(circles[j]);
                    collided_circle.insert(j);
                    break;
                }
            }
        }

        collided_circle.clear();

        // Divide the circles for physics updates among threads
        int half = circles.size() / 2;
        std::cout<<deltaTime<<"\n";

        std::thread t1(updateCirclesPhysics, std::ref(circles), 0, half, deltaTime, std::ref(window));
        std::thread t2(updateCirclesPhysics, std::ref(circles), half, circles.size(), deltaTime, std::ref(window));

        // Wait for both threads to finish
        t1.join();
         t2.join();
        // Render circles in the main thread (required by SFML)
        for (auto& circle : circles) {
            circle.setup(window);
        }

        window.display();
        window.clear();
              std::cout<<deltaTime<<"\n";
    }

    return 0;
}
// g++ objects.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
