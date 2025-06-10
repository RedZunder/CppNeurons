#include "classes.cpp"

using namespace std;



int main()
{
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(720, 720), "Screen");

	sf::Vector2f screenCenter(window.getSize().x/2, window.getSize().y / 2);


	sf::Color col;
	col.r = 255; col.g = 255; col.b = 255;

	Cell luca(50, col, 100);

	luca.setPosition(screenCenter.x - luca.getRadius(), screenCenter.y - luca.getRadius());


	luca.showInfo();
	srand(time(NULL));

	Food snack(30);
	snack.setRadius(10);
	snack.setFillColor(sf::Color::Blue);
	snack.setPosition(Vector2f(100,50));

	Vector2f foodDir(0, 0);

	while (window.isOpen())
	{
		window.setFramerateLimit(60);
		sf::Time elapsed = clock.restart();


		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		foodDir = (snack.getPosition() - luca.getPosition());
		luca.moveTo(sf::Vector2f(1,1), elapsed.asSeconds());


		// clear the window with black color
		window.clear(sf::Color::Black);



		///DRAW THINGS
		window.draw(luca);
		window.draw(snack);




		 // end the current frame
		window.display();


	}




	return 0;
}









