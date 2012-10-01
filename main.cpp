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

	// Declare and load a texture
	sf::Texture texture;
	texture.loadFromFile("texture.png");

	// Create a sprite
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.25,0.25));
	layer1.addSprite(&sprite);
	sf::Sprite sprite2;
	sprite2.setTexture(texture);
	sprite2.setScale(sf::Vector2f(0.25,0.25));
	layer2.addSprite(&sprite2);


	cout << "v0.6" << endl;

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

