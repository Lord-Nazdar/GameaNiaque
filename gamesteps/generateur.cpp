#include "../gamestep.h"
bool GameStep::generateur(){

	LayerManager layerManager;
	Layer layer1(1,0);	//Cadre
	Layer layer2(1,0);	//Virus dans cadre

	layerManager.add(&layer1);
	layerManager.add(&layer2);

	sf::RectangleShape textrect(sf::Vector2f(width-160, 50));
	textrect.setPosition(sf::Vector2f(140,45));
	textrect.setFillColor(sf::Color(0,0,0,100));

	layer1.addElement(new Element(Texture("cadre.png"),sf::Vector2f(20,20), 0.f));
	player=new Player(Player::helical);
	player->player->setPosition(sf::Vector2f(50+20-32,50+20-32));

	layer2.addElement(player->player);

	//name display
	sf::Font Arial;
	Arial.loadFromFile("pixelart.ttf");
	sf::Text name;
	name.setCharacterSize(40);
	name.setColor(sf::Color::White);
	name.setString("Ebola");
	name.setPosition(sf::Vector2f(150,45));

	std::string m_saisie="";

	unsigned int frame = 0;
	bool incColor=false;

	sf::Mouse mouse;
	sf::Event::TextEvent textEvent;

	while (window->isOpen())
	{
		stepEvent();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			if(!pauseMenu()){
				return false;
			}
		}

		if(mouse.getPosition().x>140 && mouse.getPosition().x<width-160 && mouse.getPosition().y>45 && mouse.getPosition().y<+45+50){
			if (sf::Event::TextEntered){
				if ((textEvent.unicode > 30 &&(textEvent.unicode < 127 || textEvent.unicode > 159))){
					m_saisie += static_cast<char>(textEvent.unicode);
					name.setString(m_saisie);
				}
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
		layerManager.update(frame);
		layerManager.draw(*window);
		window->draw(textrect);
		window->draw(name);
		window->display();
		frame++;
	}

	return true;
}
