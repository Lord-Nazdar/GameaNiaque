#include "gamestep.h"
#include <time.h>

GameStep::GameStep()
{
	frame=0;
}

void GameStep::init(){
	window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Game à Niaque", sf::Style::Fullscreen);
	window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(60); //Limite a 60FPS
	height=sf::VideoMode::getDesktopMode().height;
	width=sf::VideoMode::getDesktopMode().width;
	srand ( time(NULL) );
}

int GameStep::menu(){
	return 1;
}

void GameStep::pauseMenu(){	//Not very clear :(
	int activ=0;	//choice number

	sf::Texture texture;
	sf::Sprite sprite;
	texture.loadFromFile("resume.png");
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(500,0,500,200));
	sf::Texture texture2;
	sf::Sprite sprite2;
	texture2.loadFromFile("quit.png");
	sprite2.setTexture(texture2);
	sprite2.setPosition(sf::Vector2f(0,250));
	sprite2.setTextureRect(sf::IntRect(0,0,500,200));
	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
				activ++;
			if (event.type == sf::Event::KeyPressed&& event.key.code == sf::Keyboard::Return){
				if(activ%2==0){
					return;
				}
				else{
					window->close();
				}
			}
		}

		if(activ%2==0){
			sprite.setTextureRect(sf::IntRect(500,0,500,200));
			sprite2.setTextureRect(sf::IntRect(0,0,500,200));

		}
		else{
			sprite.setTextureRect(sf::IntRect(0,0,500,200));
			sprite2.setTextureRect(sf::IntRect(500,0,500,200));
		}

		window->clear();
		window->draw(sprite);
		window->draw(sprite2);
		window->display();
	}
}

bool GameStep::step1(){

}

bool GameStep::step2(){

}

bool GameStep::step3(){
	LayerManager layerManager;
	Layer layer1(0,0);	//Cell layer

	layerManager.add(&layer1);

	std::cout << height << std::endl;
	std::cout << width << std::endl;

	std::vector<MovableElement*> element;
	for(int i=0; i<rand()%5+4;i++){
		element.push_back(new MovableElement("icosahedral.png",sf::Vector2f(rand() % width,rand() % height),0));
		layer1.addElement(element[i]);
		std::cout << "et de " << i+1 << std::endl;
	}

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			pauseMenu();

		window->clear();
		layerManager.update(frame);
		layerManager.draw(*window);
		window->display();
		frame++;
	}
}

bool GameStep::step4(){

}
