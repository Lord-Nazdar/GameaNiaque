#include "../gamestep.h"
#define PERMUTER(x,y) x ^= y, y ^= x, x ^= y

void change(int *a,int *b){

  *a += *b;
  *b = *a-*b;
  *a = *a-*b;
}

bool GameStep::step2(){
	//return true;

	srand(time(NULL));

	//Layer
	LayerManager layerManager;
	//Layer layer1(1,0);	//Player cell layer
	Layer layer2(1,0);	// Big Cell
	Layer layer3(1,0);	//DNA solution
	Layer layer4(1,0);	//DNA player
	Layer layer6(1,1);	//white particles Layer
	Layer layer7(1,1);	//white2 particles Layer
	layerManager.add(&layer7);
	layerManager.add(&layer6);
	//layerManager.add(&layer1);
	layerManager.add(&layer2);
	layerManager.add(&layer3);
	layerManager.add(&layer4);

	int cran=0;
int check=1;

	//layer1.addElement(player->player); //Ajout de l'entitée player

	Element *cell;
	cell = new Element(Texture("cellule.png"),sf::Vector2f((width-500)/2,(height-500)/2), 0.f);
	cell->setScale(1.73,1.73);
	sf::Vector2f cellpos((width-(500*cell->getScale().x))/2,(height-(500*cell->getScale().y))/2);
	cell->setPosition(cellpos);
	layer2.addElement(cell);

	//text display
	sf::Font Arial = Font("pixelart.ttf");

	//Tableau de l'adn solution et player
	int adnSol[15];
	int adnPlay[15];
	for(int i=0;i<15;i++){
		adnSol[i]=rand()%4;
		adnPlay[i]=adnSol[i];
		layer3.addElement(new AnimatedElement(Texture("dna.png"),sf::Vector2f((((width/2)-480)+i*64),(height/2)-128), 0.f, 64, 1,adnSol[i]));
		layer3.addElement(new AnimatedElement(Texture("dna.png"),sf::Vector2f((((width/2)-480)+i*64),(height/2)-64), 0.f, 64, 1,4));
	}

	//Fleche
	layer3.addElement(new AnimatedElement(Texture("dna.png"),sf::Vector2f((width/2)-32,(height/2)+64), 0.f, 64, 1,5));

	//Shuffle solution
	int nbperm=rand()%30+20;
	int permDe=0;
	int permAvec=0;
	for(int i=0;i<nbperm;i++){
		permDe=rand()%15;
		permAvec=rand()%15;
		if(permDe!=permAvec)
			change(&adnPlay[permDe],&adnPlay[permAvec]);
	}

	for(int i=0;i<15;i++){
		layer4.addElement(new AnimatedElement(Texture("dna.png"),sf::Vector2f((((width/2)-480)+i*64),(height/2)), 0.f, 64, 1,adnPlay[i]));
	}


	unsigned int frame = 0;

	int outPart=3;
	change(&outPart,&adnPlay[7]);
	layer4.addElement(new AnimatedElement(Texture("dna.png"),sf::Vector2f((width/2)-32,(height/2)+128), 0.f, 64, 1,outPart));

	bool incColor=false;

	sf::Text scoreText;
	scoreText.setFont(Arial);
	scoreText.setPosition(20,20);

	bool release=true;
	bool trollpart2=true;

	while (window->isOpen() && trollpart2)
	{
		//Supprimer impérativement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
			trollpart2=false;
		}

		stepEvent();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			if(!pauseMenu()){
				return false;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&&release){
			cran--;
			if(cran<0){
				cran=14;
			}
			release=false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&release){
			cran++;
			if(cran>14){
				cran=0;
			}
			release=false;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)&&release){
			std::cout << "tableau de solution : ";
			for(int i=0;i<15;i++){
				std::cout << "[" << adnSol[i] << "];";
			}
			std::cout << "\ntableau de player : ";
			for(int i=0;i<15;i++){
				std::cout << "[" << adnPlay[i] << "];";
			}
			std::cout << "\net le cran : " << cran << std::endl;
			std::cout << "check " << check << std::endl;
			release=false;
		}

		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)||sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Keyboard::isKeyPressed(sf::Keyboard::Down))&&release){
			if(7-cran>=0)
				change(&outPart,&adnPlay[(7-cran)%15]);
			else
				change(&outPart,&adnPlay[15-((-(7-cran))%15)]);
			release=false;
		}

		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			release=true;

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
		check=1;
		if(adnPlay[15-cran]==adnSol[0]){
			while(adnPlay[((15-cran)+check)%15]==adnSol[check]){
				check++;
				if(check==14){
					score+=6000-frame;
					if(score<0)
						score=0;
					return true;
				}
			}
		}



		//Update score render
		scoreText.setString(toString(this->score));

		window->clear(sf::Color(red,22,22));
		layerManager.update(frame);
		layerManager.draw(*window);
		window->draw(scoreText);
		window->display();

		layer4.clear();
		for(int i=0;i<15;i++){
			int step =0;
			if(i+cran>=0)
				step=(i+cran)%15;
			else
				step=(15-((-(i+cran))%15));
			layer4.addElement(new AnimatedElement(Texture("dna.png"),sf::Vector2f((((width/2)-480)+step*64),(height/2)), 0.f, 64, 1,adnPlay[i]));
		}

		layer4.addElement(new AnimatedElement(Texture("dna.png"),sf::Vector2f((width/2)-32,(height/2)+128), 0.f, 64, 1,outPart));

		int white1size = white1.size();
		int white2size = white2.size();

		for(unsigned int j=0; j<white1size; j++){
			if(white1size>0 && white1.at(j)->getPosition().y>height+128){
				white1.erase(white1.begin()+j);
				white1size--;
			}
		}

		for(unsigned int j=0; j<white2size; j++){
			if(white2size>0 && white2.at(j)->getPosition().y>height+128){
				white2.erase(white2.begin()+j);
				white2size--;
			}
		}


		//spawn white1
		if(frame%30==0){
			int r = 0 + (rand() % ((width-128) - 0));
			white1.push_back(new Element(Texture("white1.png"),sf::Vector2f(r,0), 0.f));
			float srand = (rand()%5)/10.0;
			white1[white1.size()-1]->setScale(0.75+(srand),0.75+(srand));
			layer6.addElement(white1[white1.size()-1]);
		}

		//spawn white2
		if(frame%50==0){
			int r = 0 + (rand() % ((width-128) - 0));
			white2.push_back(new Element(Texture("white2.png"),sf::Vector2f(r,0), 0.f));
			float srand = (rand()%10)/10.0;
			white2[white2.size()-1]->setScale(0.75+(srand),0.75+(srand));
			layer7.addElement(white2[white2.size()-1]);
		}
		//Update white1
		for(std::vector<Element*>::iterator i = white1.begin(); i != white1.end(); i++){
			(*i)->move(0,2);
		}

		//Update white2
		for(std::vector<Element*>::iterator i = white2.begin(); i != white2.end(); i++){
			(*i)->move(0,1);
		}

		frame++;
	}
	score+=6000-frame;
	if(score<0)
		score=0;

	return true;
}

bool GameStep::step2int3(){
	//return true;

	//Layer
	LayerManager layerManager;
	Layer layer2(1,0);	// Big Cell
	Layer layer6(1,1);	//white particles Layer
	Layer layer7(1,1);	//white2 particles Layer
	layerManager.add(&layer7);
	layerManager.add(&layer6);
	layerManager.add(&layer2);

	Element *cell;
	cell = new Element(Texture("cellule.png"),sf::Vector2f((width-500)/2,(height-500)/2), 0.f);
	cell->setScale(1.73,1.73);
	sf::Vector2f cellpos((width-(500*cell->getScale().x))/2,(height-(500*cell->getScale().y))/2);
	cell->setPosition(cellpos);
	layer2.addElement(cell);

	//text display
	sf::Font Arial = Font("pixelart.ttf");
	//Text part 4 : acte
	sf::Text acte;
	acte.setFont(Arial);
	acte.setScale(1.5,1.5);
	acte.setColor(sf::Color(0,0,0,0));
	acte.setPosition(width/2-400,height/2-200);
	acte.setString("Acte 3\n     Propagation");

	unsigned int frame = 0;

	bool incColor=false;
	sf::Text scoreText;
	scoreText.setFont(Arial);
	scoreText.setPosition(20,20);

	float x =50;
	float y =50;

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

		if(frame>200 && frame<274){
			cell->setScale(1.73-((frame-200)*0.0179),1.73-((frame-200)*0.0179));
			cell->move(sf::Vector2f(moveTo(frame,cellpos.x,50,72),moveTo(frame,cellpos.y,50,72)));
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

		int white1size = white1.size();
		int white2size = white2.size();

		for(unsigned int j=0; j<white1size; j++){
			if(white1size>0 && white1.at(j)->getPosition().y>height+128){
				white1.erase(white1.begin()+j);
				white1size--;
			}
		}

		for(unsigned int j=0; j<white2size; j++){
			if(white2size>0 && white2.at(j)->getPosition().y>height+128){
				white2.erase(white2.begin()+j);
				white2size--;
			}
		}


		//spawn white1
		if(frame%30==0){
			int r = 0 + (rand() % ((width-128) - 0));
			white1.push_back(new Element(Texture("white1.png"),sf::Vector2f(r,0), 0.f));
			float srand = (rand()%5)/10.0;
			white1[white1.size()-1]->setScale(0.75+(srand),0.75+(srand));
			layer6.addElement(white1[white1.size()-1]);
		}

		//spawn white2
		if(frame%50==0){
			int r = 0 + (rand() % ((width-128) - 0));
			white2.push_back(new Element(Texture("white2.png"),sf::Vector2f(r,0), 0.f));
			float srand = (rand()%10)/10.0;
			white2[white2.size()-1]->setScale(0.75+(srand),0.75+(srand));
			layer7.addElement(white2[white2.size()-1]);
		}
		//Update white1
		for(std::vector<Element*>::iterator i = white1.begin(); i != white1.end(); i++){
			(*i)->move(0,2);
		}

		//Update white2
		for(std::vector<Element*>::iterator i = white2.begin(); i != white2.end(); i++){
			(*i)->move(0,1);
		}

		frame++;
	}

	return true;
}

