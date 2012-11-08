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


