#include "classes.cpp"

using namespace std;



int main()
{
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(480, 480), "Screen");
	sf::Vector2f screenCenter(window.getSize().x/2, window.getSize().y / 2);

	Cell luca(sf::Vector2f(300,75));

	luca.showInfo();
	
	sf::Color col;
	col.r = 100; col.g = 50; col.b = 200;

	sf::CircleShape circle;
	circle.setRadius(50);

	circle.setPosition(sf::Vector2f(screenCenter.x - circle.getRadius(), screenCenter.y - circle.getRadius()));
	circle.setFillColor(col);




	while (window.isOpen())
	{
		window.setFramerateLimit(60);
		srand(time(NULL));
		sf::Time elapsed = clock.restart();


		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}





		// clear the window with black color
		window.clear(sf::Color::Black);


		///DRAW THINGS
		window.draw(circle);

		 // end the current frame
		window.display();


	}




	return 0;
}









