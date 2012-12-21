#include "../gamestep.h"

Player* GameStep::player = NULL;

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
	window->setFramerateLimit(60); //Limite a 60FPS
	height=sf::VideoMode::getDesktopMode().height;
	width=sf::VideoMode::getDesktopMode().width;
	srand ( time(NULL) );

	//Initialisation du score
	this->score=0 ;

	//Création du player
	player=new Player;

	//Initialise le rouge pour plus de cohérence
	red=120;

	//Un run pour l'initialisation au noir
	window->clear(sf::Color(0,0,0));
	window->display();

	window->setTitle("The Ultimate Mayhem Destruction Virus");

}

bool GameStep::logo(){
	//Masquer le curseur
	window->setMouseCursorVisible(false);

	//Music maestro
	sf::Music logoMusic;
	//logoMusic=new sf::Music("logo.wav");
	logoMusic.openFromFile("music/logo.wav");
	logoMusic.play();

	Layer layer1(1,0);	//Logo apparences layer
	Layer layer2(1,0);	//Logo gameaniaque layer
	Layer layer3(1,0);	//Logo efrei layer
	Layer layer4(1,0);	//Logo game layer
	Layer layer5(1,0);	//Logo audio layer

	sf::RectangleShape fade5(sf::Vector2f(width, height));
	sf::RectangleShape fade4(sf::Vector2f(width, height));
	sf::RectangleShape fade3(sf::Vector2f(width, height));
	sf::RectangleShape fade2(sf::Vector2f(width, height));
	sf::RectangleShape fade1(sf::Vector2f(width, height));

	layer1.addElement(new Element(Texture("applogo.png"),sf::Vector2f((width/2)-346,(height/2)-111), 0.f));
	layer2.addElement(new Element(Texture("gamelogo.png"),sf::Vector2f((width/2)-346,(height/2)-59.5), 0.f));
	layer3.addElement(new Element(Texture("efreilogo.png"),sf::Vector2f((width/2)-346,(height/2)-166), 0.f));
	layer4.addElement(new Element(Texture("jeulogo.png"),sf::Vector2f((width/2)-346,(height/2)-166), 0.f));
	layer5.addElement(new Element(Texture("audiologo.png"),sf::Vector2f((width/2)-346,(height/2)-250), 0.f));

	int frame=0;
	fade1.setPosition(sf::Vector2f(0,0));
	fade1.setFillColor(sf::Color(0,0,0,255));
	fade2.setPosition(sf::Vector2f(0,0));
	fade2.setFillColor(sf::Color(0,0,0,255));
	fade3.setPosition(sf::Vector2f(0,0));
	fade3.setFillColor(sf::Color(0,0,0,255));
	fade4.setPosition(sf::Vector2f(0,0));
	fade4.setFillColor(sf::Color(0,0,0,255));
	fade5.setPosition(sf::Vector2f(0,0));
	fade5.setFillColor(sf::Color(0,0,0,255));
	while(frame<1175 && window->isOpen())
	{
		stepEvent();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			frame=1300;

		if(frame<255){
			fade1.setFillColor(sf::Color(0,0,0,255-frame));
		}
		else if(frame>260&&frame<515){
			fade2.setFillColor(sf::Color(0,0,0,255-(frame-260)));
		}
		else if(frame>520&&frame<770){
			fade3.setFillColor(sf::Color(0,0,0,255-(frame-520)));
		}
		else if(frame>770&&frame<1020){
			fade4.setFillColor(sf::Color(0,0,0,255-(frame-770)));
		}
		else if(frame>1030&&frame<1175){
			fade5.setFillColor(sf::Color(0,0,0,255-(frame-1030)));
		}


		window->clear(sf::Color(0,0,0));

		if(frame>1020&&frame<1175)
			layer5.draw(*window,sf::RenderStates::Default);
		window->draw(fade5);
		if(frame>765&&frame<1020)
			layer4.draw(*window,sf::RenderStates::Default);
		window->draw(fade4);
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
	name.setCharacterSize(30);
	name.setColor(sf::Color::Black);

	unsigned int frame = 0;
	bool incColor=false;


	sf::Music clicMusic;
	//logoMusic=new sf::Music("logo.wav");
	clicMusic.openFromFile("music/clickMenu.wav");

	int playClic=0;

	while (window->isOpen())
	{
		stepEvent();

		if(frame*3<255){
			fade1.setFillColor(sf::Color(0,0,0,255-frame*3));
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

		sf::Mouse mouse;

		if(mouse.getPosition().x>margel && mouse.getPosition().x<margel+423 && mouse.getPosition().y>margeu && mouse.getPosition().y<margeu+300 ){
			if(playClic!=1){
				clicMusic.play();
				playClic=1;
			}

			layer2.clear();
			layer2.addElement(new Element(Texture("menuMapAN.png"),sf::Vector2f(margel,margeu), 0.f));
			fill.setFillColor(sf::Color(130,130,130,255));
			fillcolor.setFillColor(sf::Color(96,64,115,255));
			fill.setPosition(mouse.getPosition().x,mouse.getPosition().y);
			fillcolor.setPosition(mouse.getPosition().x,mouse.getPosition().y);
			name.setString("Credits");
			name.setPosition(mouse.getPosition().x+40,mouse.getPosition().y);
			if(mouse.isButtonPressed(sf::Mouse::Left))
				return 7;
		}
		else if(mouse.getPosition().x>margel+200 && mouse.getPosition().x<margel+200+170 && mouse.getPosition().y>margeu+300 && mouse.getPosition().y<margeu+300+200 ){
			if(playClic!=2){
				clicMusic.play();
				playClic=2;
			}


			layer2.clear();
			layer2.addElement(new Element(Texture("menuMapAS.png"),sf::Vector2f(margel,margeu), 0.f));
			fill.setFillColor(sf::Color(130,130,130,255));
			fillcolor.setFillColor(sf::Color(226,73,17,255));
			fill.setPosition(mouse.getPosition().x,mouse.getPosition().y);
			fillcolor.setPosition(mouse.getPosition().x,mouse.getPosition().y);
			name.setString("High Score");
			name.setPosition(mouse.getPosition().x+40,mouse.getPosition().y);
			if(mouse.isButtonPressed(sf::Mouse::Left))
				return 6;
		}
		else if(mouse.getPosition().x>margel+425 && mouse.getPosition().x<margel+425+205 && mouse.getPosition().y>margeu+75 && mouse.getPosition().y<margeu+75+167 ){
			if(playClic!=3){
				clicMusic.play();
				playClic=3;
			}


			layer2.clear();
			layer2.addElement(new Element(Texture("menuMapEU.png"),sf::Vector2f(margel,margeu), 0.f));
			fill.setFillColor(sf::Color(130,130,130,255));
			fillcolor.setFillColor(sf::Color(96,174,222,255));
			fill.setPosition(mouse.getPosition().x,mouse.getPosition().y);
			fillcolor.setPosition(mouse.getPosition().x,mouse.getPosition().y);
			name.setString("Jouer");
			name.setPosition(mouse.getPosition().x+40,mouse.getPosition().y);
			if(mouse.isButtonPressed(sf::Mouse::Left))
				return 1;

		}
		else if(mouse.getPosition().x>margel+400 && mouse.getPosition().x<margel+400+216 && mouse.getPosition().y>margeu+236 && mouse.getPosition().y<margeu+236+214 ){
			if(playClic!=4){
				clicMusic.play();
				playClic=4;
			}


			layer2.clear();
			layer2.addElement(new Element(Texture("menuMapS.png"),sf::Vector2f(margel,margeu), 0.f));
			fill.setFillColor(sf::Color(130,130,130,255));
			fillcolor.setFillColor(sf::Color(216,216,204,255));
			fill.setPosition(mouse.getPosition().x,mouse.getPosition().y);
			fillcolor.setPosition(mouse.getPosition().x,mouse.getPosition().y);
			name.setString("Generateur");
			name.setPosition(mouse.getPosition().x+40,mouse.getPosition().y);
			if(mouse.isButtonPressed(sf::Mouse::Left))
				return 5;
		}
		else if(mouse.getPosition().x>margel+635 && mouse.getPosition().x<margel+635+351 && mouse.getPosition().y>margeu && mouse.getPosition().y<margeu+344 ){
			if(playClic!=5){
				clicMusic.play();
				playClic=5;
			}


			layer2.clear();
			layer2.addElement(new Element(Texture("menuMapRU.png"),sf::Vector2f(margel,margeu), 0.f));
			fill.setFillColor(sf::Color(130,130,130,255));
			fillcolor.setFillColor(sf::Color(107,110,111,255));
			fill.setPosition(mouse.getPosition().x,mouse.getPosition().y);
			fillcolor.setPosition(mouse.getPosition().x,mouse.getPosition().y);
			name.setString("Instruction");
			name.setPosition(mouse.getPosition().x+40,mouse.getPosition().y);
			if(mouse.isButtonPressed(sf::Mouse::Left))
				return 8;
		}
		else if(mouse.getPosition().x>margel+750 && mouse.getPosition().x<margel+750+170 && mouse.getPosition().y>margeu+350 && mouse.getPosition().y<margeu+350+132 ){
			if(playClic!=6){
				clicMusic.play();
				playClic=6;
			}


			layer2.clear();
			layer2.addElement(new Element(Texture("menuMapAU.png"),sf::Vector2f(margel,margeu), 0.f));
			fill.setFillColor(sf::Color(130,130,130,255));
			fillcolor.setFillColor(sf::Color(81,205,135,255));
			fill.setPosition(mouse.getPosition().x,mouse.getPosition().y);
			fillcolor.setPosition(mouse.getPosition().x,mouse.getPosition().y);
			name.setString("Quitter");
			name.setPosition(mouse.getPosition().x+40,mouse.getPosition().y);
			if(mouse.isButtonPressed(sf::Mouse::Left))
				return 10;
		}
		else{
			playClic=0;
			layer2.clear();
			fill.setFillColor(sf::Color(130,130,130,0));
			fillcolor.setFillColor(sf::Color(96,64,115,0));
			name.setString("");
			playClic=true;
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


bool GameStep::pauseMenu(){

	//Masquer le curseur
	window->setMouseCursorVisible(true);

	unsigned int frame = 0;
	bool incColor=false;

	sf::RectangleShape fill(sf::Vector2f(width, 35));
	fill.setFillColor(sf::Color(0,0,0,0));

	//text display
	sf::Font Arial = Font("pixelart.ttf");
	sf::Text continueTxt;
	continueTxt.setFont(Arial);
	continueTxt.setCharacterSize(30);
	continueTxt.setColor(sf::Color::Black);
	continueTxt.setPosition((width/2)-120,(height/2)-60);
	continueTxt.setString("Continuer");
	sf::Text menuTxt;
	menuTxt.setFont(Arial);
	menuTxt.setCharacterSize(30);
	menuTxt.setColor(sf::Color::Black);
	menuTxt.setPosition((width/2)-60,(height/2));
	menuTxt.setString("Menu");
	sf::Text quitTxt;
	quitTxt.setFont(Arial);
	quitTxt.setCharacterSize(30);
	quitTxt.setColor(sf::Color::Black);
	quitTxt.setPosition((width/2)-90,(height/2)+60);
	quitTxt.setString("Quitter");

	sf::Mouse mouse;

	int pressed=0;

	while (window->isOpen())
	{
		stepEvent();

		if(mouse.getPosition().y>(height/2)+60 && mouse.getPosition().y<(height/2)+60+30 ){
			fill.setPosition(sf::Vector2f(0,(height/2)+60));
			fill.setFillColor(sf::Color(0,0,0,50));
			if(mouse.isButtonPressed(sf::Mouse::Left)&&pressed==0)
				pressed=1;

		}
		else if(mouse.getPosition().y>(height/2)-60 && mouse.getPosition().y<(height/2)-60+30 ){
			fill.setPosition(sf::Vector2f(0,(height/2)-60));
			fill.setFillColor(sf::Color(0,0,0,50));
			if(mouse.isButtonPressed(sf::Mouse::Left)&&pressed==0)
				pressed=2;
		}
		else if(mouse.getPosition().y>(height/2) && mouse.getPosition().y<(height/2)+30 ){
			fill.setPosition(sf::Vector2f(0,(height/2)));
			fill.setFillColor(sf::Color(0,0,0,50));
			if(mouse.isButtonPressed(sf::Mouse::Left)&&pressed==0)
				pressed=3;
		}
		else{
			fill.setFillColor(sf::Color(70,70,70,0));
		}

		if(pressed!=0 && !mouse.isButtonPressed(sf::Mouse::Left)){
			switch(pressed){
				case 1:
					window->close();
					exit(0);
					break;
				case 2:
					return true;
					break;
				case 3:
					return false;
					break;
			}
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
		window->draw(fill);
		window->draw(continueTxt);
		window->draw(menuTxt);
		window->draw(quitTxt);
		window->display();

		frame ++;
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
}
