#include "../gamestep.h"

std::string intTostring(int nb){
	std::ostringstream oss;
	oss << nb;
	return oss.str();
}

float moveTo (int frame, float posFrom, float posTo, float duration){
	return (posTo-posFrom)/(duration*1.0);
}

GameStep::GameStep()
{
	frame=0;
	mouseButtonDown=false;
}

void GameStep::init(){
	window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Game à Niaque", sf::Style::Fullscreen);
	window->setVerticalSyncEnabled(true);
	window->setFramerateLimit(100); //Limite a 60FPS
	height=sf::VideoMode::getDesktopMode().height;
	width=sf::VideoMode::getDesktopMode().width;
	srand ( time(NULL) );

	//Initialisation du score
	this->score=0;

	//Création du player
	player=new Player;
}

bool GameStep::logo(){

	Layer layer1(1,0);	//Logo apparences layer
	Layer layer2(1,0);	//Logo gameaniaque layer
	Layer layer3(1,0);	//Logo efrei layer

	sf::RectangleShape fade3(sf::Vector2f(width, height));
	sf::RectangleShape fade2(sf::Vector2f(width, height));
	sf::RectangleShape fade1(sf::Vector2f(width, height));

	layer1.addElement(new Element(Texture("applogo.png"),sf::Vector2f((width/2)-346,(height/2)-111), 0.f));
	layer2.addElement(new Element(Texture("gamelogo.png"),sf::Vector2f((width/2)-346,(height/2)-59.5), 0.f));
	layer3.addElement(new Element(Texture("efreilogo.png"),sf::Vector2f((width/2)-346,(height/2)-166), 0.f));

	int frame=0;
	fade1.setPosition(sf::Vector2f(0,0));
	fade1.setFillColor(sf::Color(0,0,0,255));
	fade2.setPosition(sf::Vector2f(0,0));
	fade2.setFillColor(sf::Color(0,0,0,255));
	fade3.setPosition(sf::Vector2f(0,0));
	fade3.setFillColor(sf::Color(0,0,0,255));
	while(frame<770 && window->isOpen())
	{
		stepEvent();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			frame=765;

		if(frame<255){
			fade1.setFillColor(sf::Color(0,0,0,255-frame));
		}
		else if(frame>260&&frame<515){
			fade2.setFillColor(sf::Color(0,0,0,255-(frame-260)));
		}
		else if(frame>520&&frame<770){
			fade3.setFillColor(sf::Color(0,0,0,255-(frame-520)));
		}


		window->clear(sf::Color(0,0,0));

		if(frame>510&&frame<765)
			layer3.draw(*window,sf::RenderStates::Default);
		window->draw(fade3);
		if(frame>255&&frame<510)
			layer2.draw(*window,sf::RenderStates::Default);
		window->draw(fade2);
		if(frame<255)
			layer1.draw(*window,sf::RenderStates::Default);
		window->draw(fade1);

		window->display();
		frame++;
	}
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

void GameStep::stepEvent(){
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		/*if (event.type == sf::Event::LostFocus)
			pauseMenu();*/
		if (event.type == sf::Event::MouseButtonPressed){
			if (event.mouseButton.button == sf::Mouse::Left)
				mouseButtonDown=true;
		}
		if (event.type == sf::Event::MouseButtonReleased){
			if (event.mouseButton.button == sf::Mouse::Left)
				mouseButtonDown=false;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		pauseMenu();
}


