#include "libraries.h"

using namespace sf;

class Cell : public sf::CircleShape {
public:
    int pos_x, pos_y;

    Cell(Vector2f pos, float rad, sf::Color color)
    {
        pos_x = pos.x;
        pos_y = pos.y;
        setRadius(rad);
        setFillColor(color);

    }



    void showInfo()
    {
        std::cout << pos_x << " " << pos_y << "  " << getRadius() << std::endl;
    }





};



