#include "gamestep.h"
#include "textures.h"
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


    sf::Sprite resume_button;
    resume_button.setTexture(Texture("resume.png"));
    resume_button.setTextureRect(sf::IntRect(500,0,500,200));

    sf::Sprite quit_button;
    quit_button.setTexture(Texture("quit.png"));
    quit_button.setPosition(sf::Vector2f(0,250));
    quit_button.setTextureRect(sf::IntRect(0,0,500,200));

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
            resume_button.setTextureRect(sf::IntRect(500,0,500,200));
            quit_button.setTextureRect(sf::IntRect(0,0,500,200));

		}
		else{
            resume_button.setTextureRect(sf::IntRect(0,0,500,200));
            quit_button.setTextureRect(sf::IntRect(500,0,500,200));
		}

		window->clear();
        window->draw(resume_button);
        window->draw(quit_button);
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

    std::vector<Element*> element;
	for(int i=0; i<rand()%5+4;i++){
        element.push_back(new Element(Texture("icosahedral.png"), sf::Vector2f(rand() % width,rand() % height), 0.f));
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
