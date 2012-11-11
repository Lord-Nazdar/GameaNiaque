#include "../gamestep.h"
#include <string>
#include <fstream>

using namespace std;

bool GameStep::stepScore(){
	//Texte
	sf::Font Arial = Font("pixelart.ttf");

	sf::Text topR;
	topR.setFont(Arial);
	topR.setCharacterSize(40);
	topR.setColor(sf::Color(100,100,100));
	topR.setPosition(sf::Vector2f((width/2)-180,(height/2)-320));
	topR.setString("High Score");

	sf::RectangleShape top(sf::Vector2f(width, 45));
	top.setFillColor(sf::Color(0,0,0,150));
	top.setPosition(sf::Vector2f(0,(height/2)-320));

	//Fichier des HS
	ifstream fichier("score.hs", ios::in);
	int type, score;
	string nom, nameplayer, temps;

	fichier >> type >> nom >> score >> temps >> nameplayer;
	HighScoreElement high1(type,nom,score,temps,nameplayer,0,width,height);
	fichier >> type >> nom >> score >> temps >> nameplayer;
	HighScoreElement high2(type,nom,score,temps,nameplayer,1,width,height);
	fichier >> type >> nom >> score >> temps >> nameplayer;
	HighScoreElement high3(type,nom,score,temps,nameplayer,2,width,height);
	fichier >> type >> nom >> score >> temps >> nameplayer;
	HighScoreElement high4(type,nom,score,temps,nameplayer,3,width,height);
	fichier.close();

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
		high1.draw(*window);
		high2.draw(*window);
		high3.draw(*window);
		high4.draw(*window);
		window->draw(top);
		window->draw(topR);
		window->display();
		frame++;
	}
}

