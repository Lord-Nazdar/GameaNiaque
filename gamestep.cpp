#include "gamestep.h"
#include "textures.h"
#include <time.h>
#include "math.h"

GameStep::GameStep()
{
	frame=0;
	mouseButtonDown=false;
}

void GameStep::init(){
	window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Game à Niaque", );
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
	srand(time(NULL));
	/*----
	  Note gameplay :
	  mouvement verouiller écran gauche droite verouiller middle et bas : haut bas
	------*/
	LayerManager layerManager;
	Layer layer1(1,0);	//Cell layer
	Layer layer2(1,0);	//Laser layer
	Layer layer3(1,1);	//Enemies layer
	layerManager.add(&layer2);
	layerManager.add(&layer3);
	layerManager.add(&layer1);
	unsigned int frame=0;
	int red=120;
	bool incColor=false;
	bool fireactiv=false; //trigger when fire press

	//chargement du sprite
	sf::Vector2f pos((width/2)-32,(height/4)*3);

	AnimatedElement *player;
	player=new AnimatedElement(Texture("grid.png"), pos, 0.f, 64, 1);

	layer1.addElement(player);

	//Vector de laser et de enemies
	std::vector<AnimatedElement*> laser;
	//laser.reserve(10);
	std::vector<AnimatedElement*> enemies;
	//enemies.reserve(10);

	while (window->isOpen())
	{
		//stepEvent();

		if(frame%4==0){
			if(!incColor){
				red--;
				if(red<90)incColor=true;
			}
			else{
				red++;
				if(red>120)incColor=false;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			if(player->getPosition().y>height/2)
				player->move(sf::Vector2f(0,-8));}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			if(player->getPosition().y<height-96)
				player->move(sf::Vector2f(0,8));}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			if(player->getPosition().x>32)
				player->move(sf::Vector2f(-8,0));}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			if(player->getPosition().x<width-96)
				player->move(sf::Vector2f(8,0));}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&!fireactiv){
			laser.push_back(new AnimatedElement(Texture("laser.png"),player->getPosition(), 0.f, 64, 2));
			layer2.addElement(laser[laser.size()-1]);
			fireactiv=true;
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			fireactiv=false;

		//Update laser
		unsigned int lsize = laser.size();
		unsigned int lenemies = enemies.size();
		std::cout << "1: " << lsize << "; 2: " << lenemies << std::endl;
		for(unsigned int i=0; i<lsize; i++){
			//if((*i)->frameSize!=NULL){
				laser.at(i)->move(0,-11);
				//Destruction en cas de hors champ
				//if((*i)->getPosition().y<-128)
						//laser.erase(i);

				//Collision check !
				for(unsigned int j=0; j<lenemies; j++){
					//if((*j)->frameSize!=NULL){
						//std::cout << "laser : " << (*i)->getPosition().x << ";" << (*i)->getPosition().y << std::endl;
						//std::cout << "enemies : " << (*j)->getPosition().x << ";" << (*j)->getPosition().y << std::endl;
						if(laser.at(i)->getPosition().y>enemies.at(j)->getPosition().y && laser.at(i)->getPosition().y<enemies.at(j)->getPosition().y+64){
							if(laser.at(i)->getPosition().x>enemies.at(j)->getPosition().x && laser.at(i)->getPosition().x<enemies.at(j)->getPosition().x+64){

								laser.erase(laser.begin()+i);
								lsize--;
								//laser.reserve(10);
								enemies.erase(enemies.begin()+j);
								lenemies--;
								std::cout << "1: " << i << "; 2: " << j << std::endl;
								//enemies.reserve(10);
								std::cout << "touch " << std::endl;
							}
						}
					//}
				}
			//}
		}

		//spawn enemies
		if(frame%60==0){
			int r = 0 + (rand() % (width - 0));
			enemies.push_back(new AnimatedElement(Texture("grid.png"),sf::Vector2f(r,0), 0.f, 64, 1));
			layer3.addElement(enemies[enemies.size()-1]);
		}

		//Update enemies
		for(std::vector<AnimatedElement*>::iterator i = enemies.begin(); i != enemies.end(); i++){
			(*i)->move(0,4);
		}


		window->clear(sf::Color(red,22,22));
		layerManager.update(frame);
		layerManager.draw(*window);
		window->display();

		frame++;
	}
}

bool GameStep::step2(){

}

bool GameStep::step3(){

	int red=120;
	bool incColor=false;

	LayerManager layerManager;

	//The Z-Index seems to be broken :(
	//Just looked at the code, it's broken! Need to fix it
	Layer layer1(1,0);	//Cell layer
	Layer layer2(0,1);	//Background

	layerManager.add(&layer2);
	layerManager.add(&layer1);

	std::cout << height << std::endl;
	std::cout << width << std::endl;

	int nbWidth = width/200;
	int nbHeight = height/200;
	float gapW = (width-(nbWidth*200))/2;
	float gapH = (height-(nbHeight*200))/2;

	std::cout << "nb colonnes :" << nbWidth << std::endl;
	std::cout << "nb lignes :" << height/200 << std::endl;

    std::vector<Element*> element;

	int randfactor = (width/200)*(height/200);

	//----- Rand no repetition, very dirty -------
	int *tabRand;
	tabRand = new int[randfactor-1];

	for(int i=0; i<randfactor;i++){
		tabRand[i]=i;
	}

	for(int i=0; i<rand()%5+4;i++){
		int randValue=0;

		do{
			randValue = rand()% randfactor;
		}while(tabRand[randValue]==0);

		int value=tabRand[randValue];
		tabRand[randValue]=0;

		sf::Vector2f pos((((value-1)%nbWidth)*200)+gapW,((floor((value-1)/nbWidth))*200)+gapH);
		element.push_back(new AnimatedElement(Texture("grid.png"), pos, 0.f, 64, 1));
		layer1.addElement(element[i]);
	}

	sf::Text text("Trololol");
	text.setPosition(sf::Vector2f(width/2,height/2));



	while (window->isOpen())
	{
		stepEvent();

		if(mouseButtonDown){
			int nbCell =step3Mouse(element)!=0;
			if(nbCell!=0){
				if(text.getString()=="Trololol")
					text.setString("Mais ca veut rien dire vla !");
				else
					text.setString("Trololol");
			}

			mouseButtonDown=false;
		}

		if(frame%4==0){
			if(!incColor){
				red--;
				if(red<90)incColor=true;
			}
			else{
				red++;
				if(red>120)incColor=false;
			}
		}
		//std::cout << red << std::endl;
		window->clear(sf::Color(red,22,22));
		layerManager.update(frame);
		layerManager.draw(*window);
		window->draw(text);
		window->display();

		frame++;
	}
}

bool GameStep::step4(){

}

void GameStep::stepEvent(){
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
		if (event.type == sf::Event::LostFocus)
			pauseMenu();
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

int GameStep::step3Mouse(std::vector<Element*> element){
	int nbWidth = width/200;
	int nbHeight = height/200;
	float gapW = (width-(nbWidth*200))/2;
	float gapH = (height-(nbHeight*200))/2;

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		int mouseX = (floor((sf::Mouse::getPosition().x-gapW)/200)*200)+gapW;
		int mouseY = (floor((sf::Mouse::getPosition().y-gapH)/200)*200)+gapH;
		//std::cout << mouseX << ":" << mouseY << std::endl;
		for(int i=0; i<element.size();i++){
			sf::Vector2f position = element[i]->getPosition();
			if (position.x==mouseX && position.y==mouseY){
				return i;
			}
		}
		return 0;
	}
}
