
<<<<<<< HEAD
=======
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
	//Layer
	LayerManager layerManager;
	Layer layer1(1,0);	//Map complet
	Layer layer2(1,0);	//Map element
	layerManager.add(&layer1);
	layerManager.add(&layer2);

	//marge left up
	float margel=(width/2)-500;
	float margeu=(height/2)-250;

	layer1.addElement(new Element(Texture("menuMapC.png"),sf::Vector2f(margel,margeu), 0.f));


	/*layer2.addElement(new Element(Texture("menuMapC.png"),sf::Vector2f(margel,margeu, 0.f));
	layer2.addElement(new Element(Texture("menuMapAN.png"),sf::Vector2f(margel,margeu, 0.f));
	layer2.addElement(new Element(Texture("menuMapAS.png"),sf::Vector2f(margel,margeu, 0.f));
	layer2.addElement(new Element(Texture("menuMapAU.png"),sf::Vector2f(margel,margeu, 0.f));
	layer2.addElement(new Element(Texture("menuMapEU.png"),sf::Vector2f(margel,margeu, 0.f));
	layer2.addElement(new Element(Texture("menuMapRU.png"),sf::Vector2f(margel,margeu, 0.f));
	layer2.addElement(new Element(Texture("menuMapS.png"),sf::Vector2f(margel,margeu, 0.f));*/

	unsigned int frame = 0;
	int red = 120;
	bool incColor=false;

	while (window->isOpen())
	{
		stepEvent();

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
			layer2.clear();
			layer2.addElement(new Element(Texture("menuMapAN.png"),sf::Vector2f(margel,margeu), 0.f));
		}
		else if(mouse.getPosition().x>margel+200 && mouse.getPosition().x<margel+200+170 && mouse.getPosition().y>margeu+300 && mouse.getPosition().y<margeu+300+200 ){
			layer2.clear();
			layer2.addElement(new Element(Texture("menuMapAS.png"),sf::Vector2f(margel,margeu), 0.f));
		}
		else if(mouse.getPosition().x>margel+425 && mouse.getPosition().x<margel+425+205 && mouse.getPosition().y>margeu+75 && mouse.getPosition().y<margeu+75+167 ){
			layer2.clear();
			layer2.addElement(new Element(Texture("menuMapEU.png"),sf::Vector2f(margel,margeu), 0.f));
		}
		else if(mouse.getPosition().x>margel+400 && mouse.getPosition().x<margel+400+216 && mouse.getPosition().y>margeu+236 && mouse.getPosition().y<margeu+236+214 ){
			layer2.clear();
			layer2.addElement(new Element(Texture("menuMapS.png"),sf::Vector2f(margel,margeu), 0.f));
		}
		else if(mouse.getPosition().x>margel+635 && mouse.getPosition().x<margel+635+351 && mouse.getPosition().y>margeu && mouse.getPosition().y<margeu+344 ){
			layer2.clear();
			layer2.addElement(new Element(Texture("menuMapRU.png"),sf::Vector2f(margel,margeu), 0.f));
		}
		else if(mouse.getPosition().x>margel+750 && mouse.getPosition().x<margel+750+170 && mouse.getPosition().y>margeu+350 && mouse.getPosition().y<margeu+350+132 ){
			layer2.clear();
			layer2.addElement(new Element(Texture("menuMapAU.png"),sf::Vector2f(margel,margeu), 0.f));
		}
		else
			layer2.clear();

		window->clear(sf::Color(red,22,22));
		layerManager.update(frame);
		layerManager.draw(*window);
		window->display();

		frame++;
	}
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
	  durée ~~2min ou score > 1000
	------*/

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
	int red=120;
	bool incColor=false;
	bool fireactiv=false; //trigger when fire press

	//Score display
	sf::Font Arial;
	Arial.loadFromFile("arial.ttf");
	sf::Text scoreText;

	//Création de l'entitée player et positionnement
	player=new Player(Player::complex);
	player->player->setPosition(sf::Vector2f((width/2)-32,(height/4)*3));

	layer1.addElement(player->player);

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
				player->player->move(sf::Vector2f(0,-player->getVelocity()));}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
			if(player->player->getPosition().y<height-96)
				player->player->move(sf::Vector2f(0,player->getVelocity()));}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			if(player->player->getPosition().x>32)
				player->player->move(sf::Vector2f(-player->getVelocity(),0));}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			if(player->player->getPosition().x<width-96)
				player->player->move(sf::Vector2f(player->getVelocity(),0));}

		//Supprimer impérativement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
			trollpart1=false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&!fireactiv){
			laser.push_back(new AnimatedElement(Texture("laser.png"),player->player->getPosition(), 0.f, 64, 2,0));
			layer2.addElement(laser[laser.size()-1]);
			fireactiv=true;
			score--;
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
					this->score-=100;
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
			enemies.push_back(new AnimatedElement(Texture("grid.png"),sf::Vector2f(r,0), 0.f, 64, 1,0));
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
		scoreText.setString(intTostring(this->score));


		window->clear(sf::Color(red,22,22));
		layerManager.update(frame);
		layerManager.draw(*window);
		window->draw(scoreText);
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
}

bool GameStep::step1int2(){
	return true;

	//Layer
	LayerManager layerManager;
	Layer layer1(1,0);	//Player cell layer
	Layer layer2(1,0);	// Big Cell
	layerManager.add(&layer1);
	layerManager.add(&layer2);

	layer1.addElement(player->player); //Ajout de l'entitée player
	layer2.addElement(new AnimatedElement(Texture("cellule.png"),sf::Vector2f((width-500)/2,-50), 0.f, 500, 1,0));

	//var for ease
	sf::Vector2f startPos = player->player->getPosition();
	sf::Vector2f endPos(width/2,0);

	unsigned int frame = 0;
	int red = 120;
	bool incColor=false;

	//Score display
	sf::Font Arial;
	Arial.loadFromFile("arial.ttf");
	sf::Text scoreText;

	while (window->isOpen())
	{
		stepEvent();

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
		scoreText.setString(intTostring(this->score));

		player->player->move(sf::Vector2f(moveTo(frame+1,startPos.x,endPos.x,200),moveTo(frame,startPos.y,endPos.y,200)));

		std::cout << moveTo(frame+1,startPos.x,endPos.x,200) << ";" << moveTo(frame,startPos.y,endPos.y,200) << std::endl;

		window->clear(sf::Color(red,22,22));
		layerManager.update(frame);
		layerManager.draw(*window);
		window->draw(scoreText);
		window->display();

		frame++;
	}
}

bool GameStep::step2(){
	return true;
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
		element.push_back(new AnimatedElement(Texture("grid.png"), pos, 0.f, 64, 1,0));
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
>>>>>>> 47a9c72a31694071eab794b259a4b88698240850
