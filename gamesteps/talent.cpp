#include "../gamestep.h"

bool GameStep::talent(){
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
