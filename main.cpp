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
	Layer layer1(10);
	Layer layer2(20);

	layerManager.addLayer(&layer1);
	layerManager.addLayer(&layer2);

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
		App.display();
	}

	return 0;
}

