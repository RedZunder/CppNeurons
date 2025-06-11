#include "classes.h"

using namespace std;


int main()
{
	//-----------------------------------------DECLARATIONS

	std::vector<Cell*> drawQueue;

	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(720, 720), "Screen");

	sf::Vector2f screenCenter(window.getSize().x/2, window.getSize().y / 2);

	
	sf::Color col;
	col.r = 255; col.g = 255; col.b = 255;

	Cell luca(30, col, 80, 150);
	drawQueue.emplace_back(&luca);
	luca.vector_index = drawQueue.size() - 1;

	luca.setPosition(screenCenter.x - luca.getRadius(), screenCenter.y - luca.getRadius());


#if DEBUG==1
	luca.showInfo();
#endif


	Food snack(30, 10);
	snack.setFillColor(sf::Color::Blue);
	snack.setPosition(Vector2f(100,50));

	Vector2f foodDir(0, 0);

	//-----------------------------------------



	//-----------------------------------------MAIN LOOP
	while (window.isOpen())
	{
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

		foodDir = (snack.getPosition() - luca.getPosition());


		//approach until touch
		if (getV2Length(foodDir) > snack.getRadius() + luca.getRadius())
		{
			luca.moveTo(foodDir, elapsed.asSeconds());
		}
		else if (drawQueue.at(luca.vector_index) == &luca)
		{
			reproduceCell(&luca, &drawQueue, sf::Vector2f(rand() % 30 + 30, rand() % 20 + 10));
		}
		
		//-----------------------------------------





		// clear the window with black color
		window.clear(sf::Color::Black);



		///DRAW THINGS
		for (auto i : drawQueue)
		{
			window.draw(*i);
		}

		window.draw(snack);




		 // end the current frame
		window.display();


	}




	return 0;
}


