// I neeed to commentt this more and also my keyboard sucks f this keyboard

#ifndef objects.cpp
#define objects.cpp
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

int const density = 5;


float const pi = 3.14;


class Circle
{ private:
	sf::Vector2f aceleration;
	sf::CircleShape shape;
	sf::Vector2f position;
    float radius;
public:
 Circle(float radius, sf::Vector2f accel, sf::Vector2f velo, sf::Vector2f position):
    acceleration(accel),
    velocity(velo), position(position),
    radius(radius){
    shape.setFillColor(sf::Color::Blue);
    shape.setRadius(radius);
    shape.setPosition(position);
    }
    void update(float deltaTime) {
        sf::Vector2f final_velocity(0,0)
         final_velocity.y = velocity.y + acceleration.y*deltaTime;

         final_velocity.x  = velocity.x +
        accleration.x*deltaTime;
        // distance formula
        shape.setposition(postiion.x+.5*(velocity.x+final_velocity.x)*deltaTime,position.y+
        .5*(velocity.y+final_velocity.y)*deltaTime);

        set_manual_velo(final_velocity);
    }
    // Imma do this later
    bool checkcollosions(Circle circle) {
        sf::Vector2f other_position = circle.getPosition();

        float dist = (position.x-other_position.x)(position.x-other_position.x) + (position.y-other_position.y)(position.y-other_position.y);
        dist = std::sqrt(dist);
        if dist > radius + circle.getradius()
           { return true}
        else
            {return false}
    }
    sf::vector2f getPosition() const {
        return position;

    }
    sf::CiraleShape getradius() const {
         return shape;
    }
    void set_manual_velo(sf::Vector2f velo) {
        velocity = velo;

    }
    void handle_collosion(Circle circle) {

    }
    void setacceleration(sf::Vector2f force) {
    // wanted to create the illusion of mass so I added density
        acceleration.y = force.y/
        (density*pi*(radius*radius);

        acceleration.x = force.x/
        (density*pi*(radius*radius);
    }
    void setup(sf::RenderWindow& window) const {
     window.draw(shape);
    }

}
#endif
