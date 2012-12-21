#include "../gamestep.h"
#include <string>
#include <fstream>

using namespace std;

bool GameStep::instruction(){
	//Texte
	sf::Font Arial = Font("pixelart.ttf");
	sf::Font Times = Font("lucon.ttf");

	sf::Text topR;
	topR.setFont(Arial);
	topR.setCharacterSize(40);
	topR.setColor(sf::Color(100,100,100));
	topR.setPosition(sf::Vector2f((width/2)-155,(height/2)-320));
	topR.setString("Instructions");

	sf::RectangleShape top(sf::Vector2f(width, 45));
	top.setFillColor(sf::Color(0,0,0,150));
	top.setPosition(sf::Vector2f(0,(height/2)-320));

	//--Etape 1
	sf::RectangleShape step1(sf::Vector2f(255,295));
	step1.setFillColor(sf::Color(0,0,0,50));
	step1.setPosition(sf::Vector2f((width/2)-575,(height/2)-260));
	sf::Text etape1R;
	etape1R.setFont(Arial);
	etape1R.setCharacterSize(30);
	etape1R.setColor(sf::Color(100,100,100));
	etape1R.setPosition(sf::Vector2f((width/2)-520,(height/2)-260));
	etape1R.setString("Etape 1");
	sf::Text etape1explR;
	etape1explR.setFont(Times);
	etape1explR.setCharacterSize(15);
	etape1explR.setColor(sf::Color(100,100,100));
	etape1explR.setPosition(sf::Vector2f((width/2)-565,(height/2)-215));
	etape1explR.setString(" Vous devez triompher\ndes anticorps.\n Pour ce faire deplacez\nvous à l'aide de vos\ntouches fléchées.\n Vous pouvez aussi tirer\navec la touche espace\nafin d'éliminer les\nanticorps.\n\nAnticorps : +10\nBonus : +100\n\n Attention, si vous\npercutez un anticorps\nvous perdrez des points.");

	//--Etape 2
	sf::RectangleShape step1bis(sf::Vector2f(255, 295));
	step1bis.setFillColor(sf::Color(0,0,0,50));
	step1bis.setPosition(sf::Vector2f((width/2)-575,(height/2)+55));
	sf::Text etape2R;
	etape2R.setFont(Arial);
	etape2R.setCharacterSize(30);
	etape2R.setColor(sf::Color(100,100,100));
	etape2R.setPosition(sf::Vector2f((width/2)-520,(height/2)+55));
	etape2R.setString("Etape 2");
	sf::Text etape2explR;
	etape2explR.setFont(Times);
	etape2explR.setCharacterSize(15);
	etape2explR.setColor(sf::Color(100,100,100));
	etape2explR.setPosition(sf::Vector2f((width/2)-565,(height/2)+100));
	etape2explR.setString(" Une fois votre virus\n dans l'organisme,\nvous devez effectuer sa\nreproduction.\n Il vous suffit de\nreproduire l'ADN du\nvirus, dans l'organisme\ninfecté.\n Utilisez les touches\nfléchées pour deplacer\nla séquence et la faire\ncorrespondre,\nappuyez sur espace\npour échanger l'élément\nde réserve et l'élément\njuste au dessus.");

	//--Etape 3
	sf::RectangleShape step2(sf::Vector2f(255, 610));
	step2.setFillColor(sf::Color(0,0,0,50));
	step2.setPosition(sf::Vector2f((width/2)-275,(height/2)-260));
	sf::Text etape3R;
	etape3R.setFont(Arial);
	etape3R.setCharacterSize(30);
	etape3R.setColor(sf::Color(100,100,100));
	etape3R.setPosition(sf::Vector2f((width/2)-220,(height/2)-260));
	etape3R.setString("Etape 3");
	sf::Text etape3explR;
	etape3explR.setFont(Times);
	etape3explR.setCharacterSize(15);
	etape3explR.setColor(sf::Color(100,100,100));
	etape3explR.setPosition(sf::Vector2f((width/2)-265,(height/2)-215));
	etape3explR.setString(" Votre but, capturer les\ncellules adverses.\n\n Vous partez en haut à\ngauche, les anticorps en\nbas à droite.\n\n Clic gauche : vous\nselectionnez votre cellule\n Clic droit : vous\nl'envoyez au contact\n\n Le calcul est simple si\nle paquet envoyé est plus\nimportant que ce qui se\ntrouve sur la cellule\nvous l'avez caputré !");

	//--Etape 4
	sf::RectangleShape step3(sf::Vector2f(260, 295));
	step3.setFillColor(sf::Color(0,0,0,50));
	step3.setPosition(sf::Vector2f((width/2)+25,(height/2)-260));
	sf::Text etape4R;
	etape4R.setFont(Arial);
	etape4R.setCharacterSize(30);
	etape4R.setColor(sf::Color(100,100,100));
	etape4R.setPosition(sf::Vector2f((width/2)+75,(height/2)-260));
	etape4R.setString("Etape 4");
	sf::Text etape4explR;
	etape4explR.setFont(Times);
	etape4explR.setCharacterSize(15);
	etape4explR.setColor(sf::Color(100,100,100));
	etape4explR.setPosition(sf::Vector2f((width/2)+35,(height/2)-215));
	etape4explR.setString(" Ca y est votre\n virus est implanté dans\nla majorité des\norganismes vivants de la\nplanète.\n Il ne vous reste plus\nqu'à savourer une bonne\nboisson tout en vous\nfelicitant pour le\ntravail accomplis.\n\n Si vous disposez de\nbonus obtenu dans\nl'arbre des talents vous\npouvez les utiliser ici,\nen cliquant sur la carte.");

	//--Score
	sf::RectangleShape step3bis(sf::Vector2f(260, 295));
	step3bis.setFillColor(sf::Color(0,0,0,50));
	step3bis.setPosition(sf::Vector2f((width/2)+25,(height/2)+55));
	sf::Text scoreR;
	scoreR.setFont(Arial);
	scoreR.setCharacterSize(30);
	scoreR.setColor(sf::Color(100,100,100));
	scoreR.setPosition(sf::Vector2f((width/2)+75,(height/2)+55));
	scoreR.setString("Score");
	sf::Text scoreexplR;
	scoreexplR.setFont(Times);
	scoreexplR.setCharacterSize(15);
	scoreexplR.setColor(sf::Color(100,100,100));
	scoreexplR.setPosition(sf::Vector2f((width/2)+35,(height/2)+100));
	scoreexplR.setString(" Le score est calculé\nen fonction de votre\nrapidité dans les\ndifférentes étapes ainsi\nque de votre niveau\nde réussite.\n\n Défiez vos amis,\nbatailez vous pour\ndéterminer lequels\nd'entre vous ferait le\nmeilleurs virus.\n Le score est aussi pris\nen compte dans\nl'attribution des bonus\ndans l'arbre des talents.");

	//--Arbre de talent
	sf::RectangleShape step4(sf::Vector2f(260, 610));
	step4.setFillColor(sf::Color(0,0,0,50));
	step4.setPosition(sf::Vector2f((width/2)+350,(height/2)-260));
	sf::Text talentR;
	talentR.setFont(Arial);
	talentR.setCharacterSize(30);
	talentR.setColor(sf::Color(100,100,100));
	talentR.setPosition(sf::Vector2f((width/2)+400,(height/2)-260));
	talentR.setString("Talents");
	sf::Text talentexplR;
	talentexplR.setFont(Times);
	talentexplR.setCharacterSize(15);
	talentexplR.setColor(sf::Color(100,100,100));
	talentexplR.setPosition(sf::Vector2f((width/2)+360,(height/2)-215));
	talentexplR.setString(" L'arbre des talents\nvous permet d'obtenir\ndes bonus exclusifs,\nvous autorisant au choix\nde disposer d'avantages\npour les différentes\nétapes,ou de bonus en fin\nde partie vous\npermettant de faire\nencore plus de victimes.\n\n Vous disposez de 7\npalliers, ils se\ndeverouillent par\ntranche de 1000 points.\n\n A chaque tranche\nvous avez le choix entre\nun bonus immediat et\nun bonus de fin de partie.\n Chaque partie est de\nce fait unique !\n\n Vous devez donc\nfaire le bon choix\nau bon moment.\n\n L'avenir de l'humanite\nest entre vos mains.");


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
		window->draw(step1);
		window->draw(etape1R);
		window->draw(etape1explR);
		window->draw(step1bis);
		window->draw(etape2R);
		window->draw(etape2explR);
		window->draw(step2);
		window->draw(etape3R);
		window->draw(etape3explR);
		window->draw(step3);
		window->draw(etape4R);
		window->draw(etape4explR);
		window->draw(step3bis);
		window->draw(scoreR);
		window->draw(scoreexplR);
		window->draw(step4);
		window->draw(talentR);
		window->draw(talentexplR);
		window->display();
		frame++;
	}
}



