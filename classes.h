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
    int vector_index = 0;

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

void reproduceCell(std::vector<std::unique_ptr<Cell>> &drawQueue, size_t parentIndex, const sf::Vector2f& offset)
{
    // Take parent out of the vector 
    auto parentPtr = std::move(drawQueue[parentIndex]);

    // Spawn children based on parent
   for (int i = 0; i < 2; ++i) {
        drawQueue.emplace_back(std::make_unique<Cell>(
            parentPtr->getRadius(), parentPtr->getFillColor(), parentPtr->speedx, parentPtr->energy, parentPtr->getPosition() + offset));
    }

    // Erase parent slot
    drawQueue.erase(drawQueue.begin() + parentIndex);

#if DEBUG==1
    std::cout << "Size  " << drawQueue.size()<<std::endl;
#endif
}


void deleteFood(std::vector<std::unique_ptr<Food>> &queue, size_t index)
{
    queue.erase(queue.begin() + index);

    for (int i=0;i<queue.size();i++)
    {
        queue[i]->vector_index = i;
    }

}








Food findClosestFood(const std::vector<std::unique_ptr<Food>> &v, const Cell &obj)
{
    Food closest = *v[0];
    float dist = abs(getV2Length(obj.getPosition() -v[0]->getPosition()));

    for (auto const &i : v)
    {
        if (abs(getV2Length(obj.getPosition() - i->getPosition())) < dist)
        {
            dist = getV2Length(obj.getPosition() - i->getPosition());
            closest = *i;
        }
    }

    return closest;
}