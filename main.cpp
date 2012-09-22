#include <iostream>
#include <SFML/Graphics.hpp>
#include "layer.h"
#include "layermanager.h"

using namespace std;

int main()
{
	sf::RenderWindow App(sf::VideoMode(800, 600), "Game à Niaque");
	App.setVerticalSyncEnabled(true);
	App.setFramerateLimit(30); //Limite a 30FPS
	LayerManager layerManager;
	Layer *layer1;
	layer1 = new Layer(10);
    layerManager.push_back(layer1);

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
    layer1->push_back(&shape);


	while (App.isOpen())
	{
		sf::Event event;
		while (App.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				App.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				App.close();
		}
		App.clear();
        App.draw(layerManager);
		App.display();
	}

	return 0;
}

