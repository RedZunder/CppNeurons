#include "libraries.h"

using namespace sf;



float getV2Length(sf::Vector2f vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}




class Cell : public CircleShape {
public:
    float speed;


    Cell(float rad, Color color, float speed_, Vector2f pos = Vector2f(0.0f, 0.0f))
    {
        setPosition(pos);
        setRadius(rad);
        setFillColor(color);
        speed = speed_;
    }


    void moveTo(Vector2f direction, float time_ms)
    {
        move(Vector2f((direction.x * time_ms * speed) / getV2Length(direction), (direction.y * time_ms * speed) / getV2Length(direction)));

        std::cout << "Direction " << direction.x / getV2Length(direction) << " " << direction.y / getV2Length(direction)
            << "  Distance " << getV2Length(direction) << std::endl;
    }



    void showInfo()                                                                                     //For debugging
    {
        std::cout << getPosition().x << " " << getPosition().y << "  " << getRadius()<< std::endl;
    }





};



class Food : public CircleShape
{
public:
    float energy;

    Food(float en) { energy = en; }



};









