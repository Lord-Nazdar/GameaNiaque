#include "../gamestep.h"

bool GameStep::step2(){
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
	cell->setScale(1.73,1.73);
	cell->setPosition(sf::Vector2f((width-(500*cell->getScale().x))/2,(height-(500*cell->getScale().y))/2));
	layer2.addElement(cell);

	//text display
	sf::Font Arial;
	Arial.loadFromFile("pixelart.ttf");

	unsigned int frame = 0;

	bool incColor=false;

	sf::Text scoreText;
	scoreText.setFont(Arial);
	scoreText.setPosition(20,20);

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
		scoreText.setString(intTostring(score));

		window->clear(sf::Color(red,22,22));
		layerManager.update(frame);
		layerManager.draw(*window);
		window->draw(scoreText);
		window->display();

		frame++;
	}
}
