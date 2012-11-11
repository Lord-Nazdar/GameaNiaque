#include "../gamestep.h"
#include <string>
#include <fstream>

using namespace std;

bool GameStep::credit(){
	//Texte
	sf::Font Arial = Font("pixelart.ttf");

	sf::Text topR;
	topR.setFont(Arial);
	topR.setCharacterSize(40);
	topR.setColor(sf::Color(100,100,100));
	topR.setPosition(sf::Vector2f((width/2)-105,(height/2)-320));
	topR.setString("Credits");

	sf::RectangleShape top(sf::Vector2f(width, 45));
	top.setFillColor(sf::Color(0,0,0,150));
	top.setPosition(sf::Vector2f(0,(height/2)-320));

	//--Credits nom
	sf::RectangleShape nom1(sf::Vector2f(width, 35));
	nom1.setFillColor(sf::Color(0,0,0,50));
	nom1.setPosition(sf::Vector2f(0,(height/2)-200));
	sf::Text nom1R;
	nom1R.setFont(Arial);
	nom1R.setCharacterSize(30);
	nom1R.setColor(sf::Color(100,100,100));
	nom1R.setPosition(sf::Vector2f((width/2)-400,(height/2)-200));
	nom1R.setString("Thomas Poulet");
	sf::Text poste1R;
	poste1R.setFont(Arial);
	poste1R.setCharacterSize(15);
	poste1R.setColor(sf::Color(100,100,100));
	poste1R.setPosition(sf::Vector2f((width/2)+200,(height/2)-185));
	poste1R.setString("Developpeur, Graphiste, Sound Designer");

	//--Credits nom
	sf::RectangleShape nom2(sf::Vector2f(width, 35));
	nom2.setFillColor(sf::Color(0,0,0,50));
	nom2.setPosition(sf::Vector2f(0,(height/2)-100));
	sf::Text nom2R;
	nom2R.setFont(Arial);
	nom2R.setCharacterSize(30);
	nom2R.setColor(sf::Color(100,100,100));
	nom2R.setPosition(sf::Vector2f((width/2)-400,(height/2)-100));
	nom2R.setString("Pierre Boyer");
	sf::Text poste2R;
	poste2R.setFont(Arial);
	poste2R.setCharacterSize(15);
	poste2R.setColor(sf::Color(100,100,100));
	poste2R.setPosition(sf::Vector2f((width/2)+200,(height/2)-85));
	poste2R.setString("Developpeur");

	//--Credits date
	sf::RectangleShape date2(sf::Vector2f(width, 35));
	date2.setFillColor(sf::Color(0,0,0,50));
	date2.setPosition(sf::Vector2f(0,(height/2)));
	sf::Text dure2R;
	dure2R.setFont(Arial);
	dure2R.setCharacterSize(30);
	dure2R.setColor(sf::Color(100,100,100));
	dure2R.setPosition(sf::Vector2f((width/2)-400,(height/2)));
	dure2R.setString("Realise entre le");
	sf::Text date2R;
	date2R.setFont(Arial);
	date2R.setCharacterSize(15);
	date2R.setColor(sf::Color(100,100,100));
	date2R.setPosition(sf::Vector2f((width/2)+200,(height/2)+15));
	date2R.setString("15 octobre 2012 . 15 novembre 2012");

	//--Credits dureenaire
	sf::RectangleShape part2(sf::Vector2f(width, 250));
	part2.setFillColor(sf::Color(0,0,0,50));
	part2.setPosition(sf::Vector2f(0,(height/2)+100));
	sf::Text part2R;
	part2R.setFont(Arial);
	part2R.setCharacterSize(30);
	part2R.setColor(sf::Color(100,100,100));
	part2R.setPosition(sf::Vector2f((width/2)-200,(height/2)+100));
	part2R.setString("En partenariat avec");

	Element game(Texture("gamelogo.png"),sf::Vector2f((width/2),(height/2)+200), 0.f);
	game.setScale(0.84,0.84);
	Element efrei(Texture("efreilogo.png"),sf::Vector2f((width/2)-500,(height/2)+200), 0.f);
	efrei.setScale(0.30,0.30);


	unsigned int frame = 0;
	bool incColor=false;


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
		window->clear(sf::Color(red,22,22));
		window->draw(top);
		window->draw(topR);
		window->draw(nom1);
		window->draw(nom1R);
		window->draw(poste1R);
		window->draw(nom2);
		window->draw(nom2R);
		window->draw(poste2R);
		window->draw(date2);
		window->draw(date2R);
		window->draw(dure2R);
		window->draw(part2);
		window->draw(part2R);
		game.draw(*window);
		efrei.draw(*window);
		window->display();
		frame++;
	}
}


