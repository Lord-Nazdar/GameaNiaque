#include <iostream>
#include <SFML/Graphics.hpp>
#include "layer.h"
#include "layermanager.h"
#include "player.h"

#include "movableelement.h"

using namespace std;

int main()
{
	int frame=0;	//frame counter

	sf::RenderWindow App(sf::VideoMode::getDesktopMode(), "Game à Niaque");
	App.setVerticalSyncEnabled(true);
	App.setFramerateLimit(60); //Limite a 30FPS


	LayerManager layerManager;
	Layer layer1(0,1);

	layerManager.add(&layer1);

	MovableElement *element;
	element=new MovableElement("icosahedral.png",sf::Vector2f(0,210),0);
	layer1.addElement(element);
	layer1.moveTo(frame,sf::Vector2f(400,600),80,0);

	cout << "v0.7" << endl;

	while (App.isOpen())
	{
		sf::Event event;
		while (App.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				App.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			App.close();

		App.clear();
		layerManager.update(frame);
		layerManager.draw(App);
		App.display();
		frame++;
	}

	return 0;
}

