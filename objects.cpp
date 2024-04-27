// I neeed to commentt this more and also my keyboard sucks f this keyboard

//breaks when you full screen it cause duh
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

    const float radius;
public:
 Circle(float radius, sf::Vector2f velo, sf::Vector2f position, sf::Color color):
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

     if (check_wall(window)) {
         velocity.x *=-.8;
         force.x=0;
         acceleration.x = 0;
     }
     else {
         acceleration.y = force.y / (density * pi * (radius * radius));
         acceleration.x = force.x / (density * pi * (radius * radius));
         }
        if (check_floor_and_ceiling(window)) {
            velocity.y *=-.8; velocity.x *= .90;
            acceleration.y = 0;
        }
        else {
	 acceleration.y = force.y / (density * pi * (radius * radius));
        acceleration.x = force.x / (density * pi * (radius * radius));
        }
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
        if (dist < radius + circle.getradius())
           { return false;}
        else
            {return true;}
    }
    bool check_floor_and_ceiling(sf::RenderWindow& window) {

        unsigned int max = window.getSize().y-50;

        if (max-shape.getPosition().y<radius && velocity.y>0) {
            shape.setPosition(shape.getPosition().x,max-radius-50);
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


     else if (shape.getPosition().x-radius<0 && velocity.x<0)
     {
         return true;
     }
     return false;
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
        force += FORCE;

    }

    void setup(sf::RenderWindow& window) const {
     window.draw(shape);
    }

};
#endif
void update_circle( Circle& circle,sf::RenderWindow& window)  {
    circle.update(.1,window);
    circle.setup(window);
}
sf::Vector2f mouse_movement(sf::Vector2f position) {

return sf::Vector2f (0,0);
}

// g++ objects.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
void createCircles(std::vector<Circle>& circles) {
    circles.emplace_back(50, sf::Vector2f(0, 0), sf::Vector2f(100, 100), sf::Color::Blue);
    circles.emplace_back(50, sf::Vector2f(0, 0), sf::Vector2f(100, 200), sf::Color::White);
    circles.emplace_back(50, sf::Vector2f(0, 0), sf::Vector2f(100, 100), sf::Color::Blue);
    circles.emplace_back(50, sf::Vector2f(0, 0), sf::Vector2f(100, 100), sf::Color::Blue);
    circles.emplace_back(50, sf::Vector2f(0, 0), sf::Vector2f(150, 100), sf::Color::Red);

    circles[0].Push_constant_force(sf::Vector2f(50, 150));
    circles[1].Push_constant_force(sf::Vector2f(50, 999));
    circles[2].Push_constant_force(sf::Vector2f(100, 112));
    circles[3].Push_constant_force(sf::Vector2f(50, 180));
    circles[4].Push_constant_force(sf::Vector2f(50, 190));
}

void updateCircles(std::vector<Circle>& circles, sf::RenderWindow& window) {
    for (auto& circle : circles) {
        update_circle(circle, window);
        circle.setup(window);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML Animation");
    std::vector<Circle> circles;

    createCircles(circles);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        updateCircles(circles, window);
        window.display();
    }

    return 0;
}
