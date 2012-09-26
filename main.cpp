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
	Layer layer1(0,1);	//Background
	Layer layer2(10,-1.5);	//Moving Particles background
	Layer layer3(20,1);	//Ennemy
	Layer layer4(30,0);	//Player
	Layer layer5(40,2);	//Moving Foreground1
	Layer layer6(50,4);	//Moving Foreground2

	layerManager.add(&layer1);
	layerManager.add(&layer2);
	layerManager.add(&layer3);
	layerManager.add(&layer4);
	layerManager.add(&layer5);
	layerManager.add(&layer6);

	sf::CircleShape *shape;
	shape=new sf::CircleShape(100.f);
	shape->setFillColor(sf::Color::Green);
	layer1.push_back(shape);

	sf::CircleShape shape2(50.f);
	shape2.setFillColor(sf::Color::Red);
	layer2.push_back(&shape2);

	cout << "v0.5" << endl;

	while (App.isOpen())
	{
		sf::Event event;
		while (App.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				App.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
				App.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				layerManager.move(1,5);
		}
		App.clear();
		layerManager.draw(App);
		App.display();
	}

	return 0;
}

