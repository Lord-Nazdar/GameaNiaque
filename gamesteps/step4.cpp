#include "../gamestep.h"

bool GameStep::step4(){

	//Music maestro
	sf::Music menuMusic;
	//logoMusic=new sf::Music("logo.wav");
	menuMusic.openFromFile("music/menu.wav");
	menuMusic.play();
	menuMusic.setLoop(true);

	//Masquer le curseur
	window->setMouseCursorVisible(true);
	//Layer
	LayerManager layerManager;
	Layer layer1(1,0);	//Map complet
	Layer layer2(1,0);	//Map element
	layerManager.add(&layer1);
	layerManager.add(&layer2);

	sf::RectangleShape fill(sf::Vector2f(300, 40));
	fill.setFillColor(sf::Color(130,130,130,0));
	sf::RectangleShape fillcolor(sf::Vector2f(30, 40));
	fillcolor.setFillColor(sf::Color(96,64,115,0));

	sf::RectangleShape fade1(sf::Vector2f(width, height));
	fade1.setPosition(sf::Vector2f(0,0));
	fade1.setFillColor(sf::Color(0,0,0,255));

	//marge left up
	float margel=(width/2)-500;
	float margeu=(height/2)-250;

	layer1.addElement(new Element(Texture("menuMapC.png"),sf::Vector2f(margel,margeu), 0.f));

	//name display
	sf::Font Arial = Font("pixelart.ttf");
	sf::Text name;
	name.setFont(Arial);
	name.setCharacterSize(60);
	name.setColor(sf::Color::White);
	name.setPosition(width/2,(height/2)-60);

	unsigned int frame = 0;
	bool incColor=false;


	sf::Music clicMusic;
	//logoMusic=new sf::Music("logo.wav");
	clicMusic.openFromFile("music/clickMenu.wav");

	int scoreaff=0;

	while (window->isOpen())
	{
		stepEvent();

		if(frame*3<255){
			fade1.setFillColor(sf::Color(0,0,0,255-frame*3));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			if(!pauseMenu()){
				return false;
			}
		}

		if(scoreaff<score){
			name.setString(toString(scoreaff));
			scoreaff+=(score/500);
		}

		if(scoreaff>1666){
			layer2.addElement(new Element(Texture("menuMapAN.png"),sf::Vector2f(margel,margeu), 0.f));
		}
		if(scoreaff>3332){
			layer2.addElement(new Element(Texture("menuMapAS.png"),sf::Vector2f(margel,margeu), 0.f));
		}
		if(scoreaff>4998){
			layer2.addElement(new Element(Texture("menuMapEU.png"),sf::Vector2f(margel,margeu), 0.f));
		}
		if(scoreaff>4998){
			layer2.addElement(new Element(Texture("menuMapEU.png"),sf::Vector2f(margel,margeu), 0.f));
		}
		if(scoreaff>6664){
			layer2.addElement(new Element(Texture("menuMapS.png"),sf::Vector2f(margel,margeu), 0.f));
		}
		if(scoreaff>8330){
			layer2.addElement(new Element(Texture("menuMapRU.png"),sf::Vector2f(margel,margeu), 0.f));
		}
		if(scoreaff>9996){
			layer2.addElement(new Element(Texture("menuMapAU.png"),sf::Vector2f(margel,margeu), 0.f));
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

		window->clear(sf::Color(red,22,22));
		layerManager.update(frame);
		layerManager.draw(*window);
		window->draw(fill);
		window->draw(fillcolor);
		window->draw(name);
		window->draw(fade1);
		window->display();

		frame++;
	}
}
