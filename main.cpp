#include "classes.h"

using namespace std;


int main()
{
	//-----------------------------------------DECLARATIONS

	std::vector<unique_ptr<Cell>> cellQueue;
	std::vector<unique_ptr<Food>> foodQueue;

	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(720, 720), "Screen");

	sf::Vector2f screenCenter(window.getSize().x / 2, window.getSize().y / 2);

	
	sf::Color col;
	col.r = 255; col.g = 255; col.b = 255;

	cellQueue.emplace_back(std::make_unique<Cell>(30, col, 80, 150));

	cellQueue[0]->vector_index = cellQueue.size() - 1;

	cellQueue[0]->setPosition(screenCenter.x - cellQueue[0]->getRadius(), screenCenter.y - cellQueue[0]->getRadius());
	
	
#if DEBUG==1
	cellQueue[0]->showInfo();
#endif

	
	//Create food pallets randomly around the place
	for (int i = 0 ; i < 20 ; i++)
	{
		srand(i * time(NULL));
		foodQueue.emplace_back(std::make_unique<Food>(30, 10));
		foodQueue[i]->vector_index = i;
		foodQueue[i]->setFillColor(sf::Color::Blue);
		foodQueue[i]->setPosition(Vector2f(rand() % window.getSize().x, rand() % window.getSize().y));
	}

	Vector2f foodDir(0, 0);
	Food closestFood(30, 10);
	//-----------------------------------------


	//-----------------------------------------MAIN LOOP
	while (window.isOpen())
	{
		//config
		window.setFramerateLimit(60);
		sf::Time elapsed = clock.restart();
		srand(time(NULL));



		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}



		//-----------------------------------------CALCULATE MOVEMENT
		

		for (int i = 0; i < cellQueue.size(); i++)
		{
			closestFood = findClosestFood(foodQueue, *cellQueue[i]);
			foodDir = (closestFood.getPosition() - cellQueue[i]->getPosition());

			//approach until touch
			if (getV2Length(foodDir) > closestFood.getRadius() + cellQueue[i]->getRadius())
			{
				cellQueue[i]->moveTo(foodDir, elapsed.asSeconds());
			}
			else
			{
				reproduceCell(cellQueue, i, sf::Vector2f((rand() % 4 - 2) * 20, (rand() % 4 - 2) * 20));
				deleteFood(foodQueue,closestFood.vector_index);
			}
		}


		
		
		//-----------------------------------------





		// clear the window with black color
		window.clear(sf::Color::Black);



		///--------------------------------------------DRAW THINGS

		for (auto &i : cellQueue)
		{
			window.draw(*i);
		}

		for (auto &i :foodQueue)
		{
			window.draw(*i);
		}




		 // end the current frame
		window.display();


	}
	



	return 0;
}


