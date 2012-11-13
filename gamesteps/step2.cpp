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
	cell->setPosition(sf::Vector2f((width-(500*cell->getScale().x))/2,(height-(500*cell->getScale().y))/2));
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

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&release){
			if(7-cran>=0)
				change(&outPart,&adnPlay[(7-cran)%15]);
			else
				change(&outPart,&adnPlay[15-((-(7-cran))%15)]);
			release=false;
		}

		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&!sf::Keyboard::isKeyPressed(sf::Keyboard::R))
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
				if(check==14)
					return true;
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

		frame++;
	}

	return true;
}
