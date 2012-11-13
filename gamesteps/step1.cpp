#include "../gamestep.h"

bool GameStep::prestep1(){
	//return true;


	sf::RectangleShape fade1(sf::Vector2f(width, height));
	fade1.setPosition(sf::Vector2f(0,0));
	fade1.setFillColor(sf::Color(0,0,0,255));
	//Layer
	LayerManager layerManager;
	//Layer layer1(1,0);	//	Player cell layer
	Layer layer2(1,0);	// logo

	//layerManager.add(&layer1);
	layerManager.add(&layer2);

	//player=new Player(Player::helical);
	//player->player->setPosition(sf::Vector2f((width/2)-32,(height/4)*3));
//	layer1.addElement(player->player);

	Element *efrei;
	efrei = new Element(Texture("efreilogo.png"),sf::Vector2f((width-346)/2,-332), 0.f);
	efrei->setPosition(((width/2)-400)+30,-150);
	efrei->setScale(0.4,0.4);
	layer2.addElement(efrei);
	Element *game;
	game = new Element(Texture("gamelogo.png"),sf::Vector2f((width-346)/2,-119), 0.f);
	game->setPosition((width/2)+30,-100);
	game->setScale(0.5,0.5);
	layer2.addElement(game);

	unsigned int frame = 0;

	bool incColor=false;

	//text display
	sf::Font Arial = Font("pixelart.ttf");

	//Text part 1 : nom
	sf::Text avec;
	avec.setFont(Arial);
	avec.setColor(sf::Color(100,100,100));
	avec.setPosition((width/2)-400,-150);
	avec.setString("Une realisation de");
	sf::Text nom;
	nom.setFont(Arial);
	nom.setColor(sf::Color(120,120,120));
	nom.setPosition(((width/2)-400)+30,-100);
	nom.setString("Pierre Boyer \n Thomas Poulet");

	//Text part 2 : concour
	sf::Text cadre;
	cadre.setFont(Arial);
	cadre.setColor(sf::Color(100,100,100));
	cadre.setPosition((width/2),-150);
	cadre.setString("Dans le cadre de");

	//Text part 3 : efrei
	sf::Text sout;
	sout.setFont(Arial);
	sout.setColor(sf::Color(100,100,100));
	sout.setPosition((width/2)-400,-200);
	sout.setString("Avec le soutient de");

	//Text part 4 : acte
	sf::Text acte;
	acte.setFont(Arial);
	acte.setScale(1.5,1.5);
	acte.setColor(sf::Color(0,0,0,0));
	acte.setPosition(width/2-400,height/2-200);
	acte.setString("Acte 1\n     Contamination");

	while (window->isOpen() && frame<700)
	{
		stepEvent();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			if(!pauseMenu()){
				return false;
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
		if(frame<40){
			fade1.setFillColor(sf::Color(0,0,0,255-frame*5));
		}

		if(frame>20){
			avec.move(0,moveTo(0,-20,height+100,200));
			nom.move(0,moveTo(0,-20,height+100,200));
		}
		if(frame>100){
			cadre.move(0,moveTo(0,-20,height+100,200));
			game->move(0,moveTo(0,-20,height+100,200));
		}
		if(frame>200){
			sout.move(0,moveTo(0,-20,height+100,200));
			efrei->move(0,moveTo(0,-20,height+100,200));
		}
		if(frame>450 && frame <550){
			acte.setColor(sf::Color(0,0,0,(frame-450)*2.5));
		}


		window->clear(sf::Color(red,22,22));
		layerManager.update(frame);
		layerManager.draw(*window);
		window->draw(nom);
		window->draw(cadre);
		window->draw(avec);
		window->draw(sout);
		window->draw(acte);
		window->draw(fade1);
		window->display();

		frame++;
	}

	//remise à 0 du tier
	this->tier=1;

	return true;
}

bool GameStep::step1(){
	//return true;

	srand(time(NULL));
	/*----
	  Note gameplay :
	  mouvement verouiller écran gauche droite verouiller middle et bas : haut bas
	  durée ~~2min ou score > 1000
	------*/

	//Masquer le curseur
	window->setMouseCursorVisible(false);

	LayerManager layerManager;
	Layer layer1(1,0);	//Player cell layer

	//--------Warning:do not add anything other on them---------
	Layer layer2(1,0);	//Laser layer
	Layer layer3(1,1);	//Enemies layer
	Layer layer4(1,0);	//Explosion layer
	Layer layer5(1,1);	//Bonus Layer
	layerManager.add(&layer2);
	layerManager.add(&layer3);
	layerManager.add(&layer4);
	layerManager.add(&layer5);
	layerManager.add(&layer1);
	unsigned int frame=0;

	bool incColor=false;
	bool fireactiv=false; //trigger when fire press

	//Score display
	sf::Font Arial = Font("pixelart.ttf");
	sf::Text scoreText;
	scoreText.setFont(Arial);
	scoreText.setPosition(20,20);

	sf::Text tabText;
	tabText.setFont(Arial);
	tabText.setCharacterSize(50);
	tabText.setPosition(width-150+20,20);
	tabText.setString("Tab");
	tabText.setColor(sf::Color(0,0,0,0));

	//Création de l'entitée player et positionnement
	//player=new Player(Player::helical);
	player->player->setPosition(sf::Vector2f((width/2)-32,(height/4)*3));

	layer1.addElement(player->player);

	//Sound effets
	sf::Music exploMusic;
	exploMusic.openFromFile("music/explo.wav");
	exploMusic.setVolume(10);
	sf::Music tirMusic;
	tirMusic.openFromFile("music/tir.wav");
	tirMusic.setVolume(10);

	//Vector de laser et de enemies
	std::vector<AnimatedElement*> laser;
	std::vector<AnimatedElement*> enemies;
	std::vector<AnimatedElement*> bonus;

	//Vector for lifetime
	std::vector<int> exploLifeTime;
	sf::Clock clock1;

	//Pour tricher et passer d'un coup
	bool trollpart1=true;

	while (window->isOpen() && (this->score<1000 || clock1.getElapsedTime().asSeconds()<120 ) && trollpart1)
	{
		stepEvent();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			if(!pauseMenu()){
				return false;
			}
		}

		if(this->score>=1000*tier){
			tabText.setColor(sf::Color(0,0,0,0+(frame%255)));
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
				tier++;
				talent();
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
			if(player->player->getPosition().y>height/2)
				player->player->move(sf::Vector2f(0,-player->velocity));}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			if(player->player->getPosition().y<height-96)
				player->player->move(sf::Vector2f(0,player->velocity));}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			if(player->player->getPosition().x>32)
				player->player->move(sf::Vector2f(-player->velocity,0));}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			if(player->player->getPosition().x<width-96)
				player->player->move(sf::Vector2f(player->velocity,0));}

		//Supprimer impérativement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
			trollpart1=false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&!fireactiv){
			laser.push_back(new AnimatedElement(Texture("laser.png"),player->player->getPosition(), 0.f, 64, 2,0));
			layer2.addElement(laser[laser.size()-1]);
			fireactiv=true;
			this->score--;
			tirMusic.play();
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			fireactiv=false;


		using namespace std;

		//Size of vector
		unsigned int lsize = laser.size();
		unsigned int lenemies = enemies.size();

		//Update laser
		for(unsigned int i=0; i<lsize; i++){
			laser.at(i)->move(0,-11);

			//Collision check!
			for(unsigned int j=0; j<lenemies; j++){

				if(lsize>0 && lenemies>0 && laser.at(i)->getPosition().y>enemies.at(j)->getPosition().y-64 && laser.at(i)->getPosition().y<enemies.at(j)->getPosition().y+64){
					if(laser.at(i)->getPosition().x>enemies.at(j)->getPosition().x-64 && laser.at(i)->getPosition().x<enemies.at(j)->getPosition().x+64){
						//Generate explosion effect
						layer4.addElement(new AnimatedElement(Texture("explo.png"),enemies.at(j)->getPosition(), 0.f, 64, 5,0));
						exploLifeTime.push_back(5);

						//Delete the laser
						laser.erase(laser.begin()+i);
						layer2.erase(i);
						lsize--;

						//Delete the enemie
						enemies.erase(enemies.begin()+j);
						layer3.erase(j);
						lenemies--;

						//inc score
						this->score+=10;

						exploMusic.play();

					}

					//An cas de double suppression
					if(lenemies-1<j)
						j--;
					if(lsize-1<i)
						i--;
				}

				//Delete enemie if too low
				else if(lenemies>0 && enemies.at(j)->getPosition().y>height+128){
					enemies.erase(enemies.begin()+j);
					layer3.erase(j);
					lenemies--;
				}

				if(lenemies-1<j)
					j--;
			}

			//Delete laser if too high
			if(lsize>0 && laser.at(i)->getPosition().y<-128){
				laser.erase(laser.begin()+i);
				layer2.erase(i);
				lsize--;
			}

			if(lsize-1<i)
				i--;
		}

		//Collision enemies player check
		for(unsigned int j=0; j<lenemies; j++){
			//Contact avec le joueur
			if(lenemies>0 && player->player->getPosition().y>enemies.at(j)->getPosition().y-64 && player->player->getPosition().y<enemies.at(j)->getPosition().y+64){
				if(player->player->getPosition().x>enemies.at(j)->getPosition().x-64 && player->player->getPosition().x<enemies.at(j)->getPosition().x+64){
					this->score-=100/(1+(player->resistance/10));
					//Delete the enemie
					enemies.erase(enemies.begin()+j);
					layer3.erase(j);
					lenemies--;
				}
			}
			if(lenemies-1<j)
				j--;
		}

		//Collision bonus player check
		for(unsigned int j=0; j<bonus.size(); j++){
			//Contact avec le joueur
			if(player->player->getPosition().y>bonus.at(j)->getPosition().y-64 && player->player->getPosition().y<bonus.at(j)->getPosition().y+64){
				if(player->player->getPosition().x>bonus.at(j)->getPosition().x-64 && player->player->getPosition().x<bonus.at(j)->getPosition().x+64){
					this->score+=100;
					//Delete the enemie
					bonus.erase(bonus.begin()+j);
					layer5.erase(j);
				}
			}
		}

		//spawn enemies
		if(frame%60==0){
			int r = 0 + (rand() % ((width-128) - 0));
			enemies.push_back(new AnimatedElement(Texture("grid.png"),sf::Vector2f(r,0), 0.f, 64, 1,24));
			layer3.addElement(enemies[enemies.size()-1]);
		}
		//spawn bonuses
		if((frame+10)%600==0){
			int r = 0 + (rand() % ((width-128) - 0));
			bonus.push_back(new AnimatedElement(Texture("tgs.png"),sf::Vector2f(r,0), 0.f, 64, 1,0));
			layer5.addElement(bonus[bonus.size()-1]);
		}

		//Update enemies
		for(std::vector<AnimatedElement*>::iterator i = enemies.begin(); i != enemies.end(); i++){
			(*i)->move(0,4);
		}

		//Update bonuses
		for(std::vector<AnimatedElement*>::iterator i = bonus.begin(); i != bonus.end(); i++){
			(*i)->move(0,6);
		}

		//Update explo every 12 frames
		if(frame%9==0){
			for(unsigned int i=0; i<exploLifeTime.size(); i++){
				if(exploLifeTime.at(i)>-1)
					exploLifeTime.at(i)--;
				else
				{
					exploLifeTime.erase(exploLifeTime.begin()+i);
					layer4.erase(i);
				}
			}
		}

		if(this->score<0)
			this->score=0;

		//Update score render
		scoreText.setString(toString(this->score));


		window->clear(sf::Color(red,22,22));
		layerManager.update(frame);
		layerManager.draw(*window);
		window->draw(scoreText);
		window->draw(tabText);
		window->display();

		frame++;
	}

	int endframe=frame;
	unsigned int lenemies = enemies.size();

	//Supression de tout les enemies et création explosion
	for(unsigned int j=0; j<lenemies; j++){
		//Generate explosion effect
		layer4.addElement(new AnimatedElement(Texture("explo.png"),enemies.at(j)->getPosition(), 0.f, 64, 5,0));
		exploLifeTime.push_back(5);
	}

	enemies.clear();
	layer3.clear();

	while(frame<endframe+60){
		//Update explo every 12 frames
		if(frame%7==0){
			for(unsigned int i=0; i<exploLifeTime.size(); i++){
				if(exploLifeTime.at(i)>-1)
					exploLifeTime.at(i)--;
				else
				{
					exploLifeTime.erase(exploLifeTime.begin()+i);
					layer4.erase(i);
				}
			}
		}
		window->clear(sf::Color(red,22,22));
		layerManager.update(frame);
		layerManager.draw(*window);
		window->draw(scoreText);
		window->display();
		frame++;
	}

	return true;
}

bool GameStep::step1int2(){
	//return true;

	//Layer
	LayerManager layerManager;
	Layer layer1(1,0);	//Player cell layer
	Layer layer2(1,0);	// Big Cell
	layerManager.add(&layer1);
	layerManager.add(&layer2);

	layer1.addElement(player->player); //Ajout de l'entitée player

	Element *cell;
	cell = new Element(Texture("cellule.png"),sf::Vector2f((width-500)/2,(height-500)/2), 0.f);
	layer2.addElement(cell);

	//var for ease
	sf::Vector2f startPos = player->player->getPosition();
	sf::Vector2f endPos(width/2,(height/2)-50);

	//text display
	sf::Font Arial = Font("pixelart.ttf");
	//Text part 4 : acte
	sf::Text acte;
	acte.setFont(Arial);
	acte.setScale(1.5,1.5);
	acte.setColor(sf::Color(0,0,0,0));
	acte.setPosition(width/2-400,height/2-200);
	acte.setString("Acte 2\n     Reproduction");

	unsigned int frame = 0;

	bool incColor=false;
	sf::Text scoreText;
	scoreText.setFont(Arial);
	scoreText.setPosition(20,20);

	while (window->isOpen())
	{
		stepEvent();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			if(!pauseMenu()){
				return false;
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



		//Update score render
		scoreText.setString(toString(this->score));

		if(frame<200)
			player->player->move(sf::Vector2f(moveTo(frame+1,startPos.x,endPos.x,200),moveTo(frame,startPos.y,endPos.y,200)));
		else if(frame>200 && frame<274){
			cell->setScale(1+(frame-200.0)/100,1+(frame-200.0)/100);
			cell->setPosition(sf::Vector2f((width-(500*cell->getScale().x))/2,(height-(500*cell->getScale().y))/2));
		}
		if(frame>274 && frame <374){
			acte.setColor(sf::Color(0,0,0,(frame-274)*2.5));
		}
		if(frame>450){
			return true;
		}

		window->clear(sf::Color(red,22,22));
		layerManager.update(frame);
		layerManager.draw(*window);
		window->draw(scoreText);
		window->draw(acte);
		window->display();

		frame++;
	}

	return true;
}
