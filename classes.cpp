#include "libraries.h"

using namespace sf;

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
        move(Vector2f((direction.x * time_ms * speed)/sqrt(direction.x* direction.x + direction.y* direction.y),
            (direction.y * time_ms * speed) / sqrt(direction.x * direction.x + direction.y * direction.y)));
        
        std::cout << "Dir " << direction.x / sqrt((direction.x * direction.x) + (direction.y * direction.y)) << "  " <<
            direction.y / sqrt((direction.x * direction.x) + (direction.y * direction.y)) << std::endl;
    }

    

    void showInfo()                                                                                     //For debugging
    {
        std::cout << getPosition().x << " " << getPosition().y << "  " << getRadius() << std::endl;
    }





};



class Food : public CircleShape
{
public:
    float energy;

    Food(float en) { energy = en; }



};










