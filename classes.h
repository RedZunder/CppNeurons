#include "libraries.h"

using namespace sf;


/**
*   @brief          Return the length of a sf::Vector2f vector
*   @param  vec     The vector
*
*   @return         Length of vector
*/
float getV2Length(sf::Vector2f vec)
{
    return sqrt(vec.x * vec.x + vec.y * vec.y);
}







class Cell : public CircleShape {
public:
    float speedx, speedy, energy;
    int top_edge, btm_edge, left_edge, rgt_edge;
    int vector_index=0;
    Cell(float rad, Color color, float speed_, float energy_, Vector2f pos = Vector2f(0.0f, 0.0f))
    {
        setPosition(pos);
        setRadius(rad);
        setOrigin(getRadius(), getRadius());
        setFillColor(color);
        speedx = speed_;
        speedy = speed_;
        energy = energy_;

        top_edge = roundf(getGlobalBounds().top);
        btm_edge = roundf(getGlobalBounds().height);
        left_edge = roundf(getGlobalBounds().left);
        rgt_edge = roundf(getGlobalBounds().width);
    }


    void moveTo(Vector2f direction, float time_ms)
    {
        move(Vector2f((direction.x * time_ms * speedx) / getV2Length(direction), (direction.y * time_ms * speedy) / getV2Length(direction)));

#if DEBUG==1

        std::cout << "Direction " << direction.x / getV2Length(direction) << " " << direction.y / getV2Length(direction)
            << "  Distance " << getV2Length(direction) << std::endl;
        std::cout << "Borders " << top_edge << " " << btm_edge << " " << left_edge << " " << rgt_edge <<std::endl;
#endif
    }







#if DEBUG==1
    void showInfo()                                                                                     //For debugging
    {
        std::cout << getPosition().x << " " << getPosition().y << "  " << getRadius()<< std::endl;
    }
#endif





};



class Food : public CircleShape
{
public:
    float energy;
    int top_edge, btm_edge, left_edge, rgt_edge;

    Food(float en, float radius) 
    {
        energy = en;
        top_edge = roundf(getGlobalBounds().top);
        btm_edge = roundf(getGlobalBounds().height);
        left_edge = roundf(getGlobalBounds().left);
        rgt_edge = roundf(getGlobalBounds().width);
        setRadius(radius);
        setOrigin(getRadius(), getRadius());
    }



};


void reproduceCell(Cell* cell, std::vector<Cell*> *drawQueue, Vector2f offset)
{
    static Cell c1(cell->getRadius(), cell->getFillColor(), cell->speedx, cell->energy, cell->getPosition() + offset);
    
    static Cell c2(cell->getRadius(), cell->getFillColor(), cell->speedx, cell->energy,cell->getPosition() -offset);

    drawQueue->emplace_back(&c1);
    drawQueue->emplace_back(&c2);

    drawQueue->erase(drawQueue->begin() + cell->vector_index);
    std::cout << "Size of vector " << drawQueue->size();
}







