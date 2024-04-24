// I neeed to commentt this more and also my keyboard sucks f this keyboard

#ifndef circle_H
#define circle_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

int const density = 5;


float const pi = 3.14;


class Circle
{ private:
	sf::Vector2f force;
    sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::CircleShape shape;
	sf::Vector2f position;
    float radius;
public:
 Circle(float radius, sf::Vector2f accel, sf::Vector2f velo, sf::Vector2f position):
    force(0,0),
    acceleration(accel),
    velocity(velo), position(position),
    radius(radius){
    shape.setFillColor(sf::Color::Blue);
    shape.setRadius(radius);
    shape.setPosition(position);
    }
    void update(float deltaTime) {
	 acceleration.y = force.y / (density * pi * (radius * radius));
        acceleration.x = force.x / (density * pi * (radius * radius));

        sf::Vector2f final_velocity(0, 0);
        final_velocity.y = velocity.y + acceleration.y * deltaTime;
        final_velocity.x = velocity.x + acceleration.x * deltaTime;

        // Update position using the distance formula
        shape.setPosition(position.x + 0.5f * (velocity.x + final_velocity.x) * deltaTime,
                           position.y + 0.5f * (velocity.y + final_velocity.y) * deltaTime);

        set_manual_velo(final_velocity);
    }
    // Imma do this later
    bool checkcollosions(const Circle& circle) {
        sf::Vector2f other_position = circle.getPosition();

        float dist = (position.x - other_position.x) * (position.x - other_position.x) +
             (position.y - other_position.y) * (position.y - other_position.y);
        dist = std::sqrt(dist);
        if (dist > radius + circle.getradius())
           { return true;}
        else
            {return false;}
    }
    sf::Vector2f getPosition() const {
        return position;

    }
    void setposition(sf::Vector2f new_position) {
	position = new_position;
	shape.setPosition(position);
    }
    float getradius() const {
         return radius;
    }
    void set_manual_velo(sf::Vector2f velo) {
        velocity = velo;

    }
    /* I'll ask dunc for help

    void handle_elastic_collosion(Circle circle) {
     // dis sucks
        float mass = pi*density*radius*radius;

        float other_mass = pi*density*circle.getradius()*circle.getradius();
        // use kenetic energy to find velocity I hate physics

    }
    void handle_inelastic_collsion {

    }
    */

    void Push_constant_force(sf::Vector2f FORCE) {
        force.x += FORCE.x;
	force.y += FORCE.y;
    }

    void setup(sf::RenderWindow& window) const {
     window.draw(shape);
    }

};
#endif

// g++ objects.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
