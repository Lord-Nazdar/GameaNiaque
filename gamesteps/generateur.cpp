#include "../gamestep.h"
bool GameStep::generateur(){

	LayerManager layerManager;
	Layer layer1(1,0);	//Cadre
	Layer layer2(1,0);	//Virus dans cadre

	layerManager.add(&layer1);
	layerManager.add(&layer2);

	player=new Player(Player::helical);
	player->player->setPosition(sf::Vector2f((width/2)-300+16,(height/2)-260+16));

	layer2.addElement(player->player);

	int freepoints=17;
	int valprop=0;
	int valrepro=0;
	int valresis=0;

	//Texte
	sf::Font Arial = Font("pixelart.ttf");

	sf::Text topR;
	topR.setFont(Arial);
	topR.setCharacterSize(40);
	topR.setColor(sf::Color(100,100,100));
	topR.setPosition(sf::Vector2f((width/2)-155,(height/2)-320));
	topR.setString("Generateur");
	sf::RectangleShape top(sf::Vector2f(width, 45));
	top.setFillColor(sf::Color(0,0,0,150));
	top.setPosition(sf::Vector2f(0,(height/2)-320));

	//frame
	sf::RectangleShape frameR(sf::Vector2f(100,100));
	frameR.setFillColor(sf::Color(0,0,0,50));
	frameR.setPosition(sf::Vector2f((width/2)-300,(height/2)-260));
	sf::RectangleShape frameLR(sf::Vector2f(45,45));
	frameLR.setFillColor(sf::Color(0,0,0,40));
	frameLR.setPosition(sf::Vector2f((width/2)-300,(height/2)-150));
	Element arrowLF(Texture("arrow.png"),sf::Vector2f((width/2)-300+45,(height/2)-150+47), 180.f);
	sf::RectangleShape frameRR(sf::Vector2f(45,45));
	frameRR.setFillColor(sf::Color(0,0,0,50));
	frameRR.setPosition(sf::Vector2f((width/2)-245 ,(height/2)-150));
	Element arrowRF(Texture("arrow.png"),sf::Vector2f((width/2)-245,(height/2)-150), 0.f);

	//Nom
	sf::RectangleShape nomR(sf::Vector2f(450,50));
	nomR.setFillColor(sf::Color(0,0,0,50));
	nomR.setPosition(sf::Vector2f((width/2)-150,(height/2)-200));
	sf::Text nomTopR;
	nomTopR.setFont(Arial);
	nomTopR.setCharacterSize(30);
	nomTopR.setColor(sf::Color::Black);
	nomTopR.setPosition(sf::Vector2f((width/2)+30,(height/2)-240));
	nomTopR.setString("Nom");
	sf::Text nomContR;
	nomContR.setFont(Arial);
	nomContR.setCharacterSize(30);
	nomContR.setColor(sf::Color::Black);
	nomContR.setPosition(sf::Vector2f((width/2)-140,(height/2)-190));
	std::string m_saisie="Ebola";
	nomContR.setString(m_saisie);

	//Propagation
	sf::RectangleShape propR(sf::Vector2f(600,50));
	propR.setFillColor(sf::Color(0,0,0,50));
	propR.setPosition(sf::Vector2f((width/2)-300,(height/2)-20));
	sf::Text propTopR;
	propTopR.setFont(Arial);
	propTopR.setCharacterSize(30);
	propTopR.setColor(sf::Color::Black);
	propTopR.setPosition(sf::Vector2f((width/2)-230,(height/2)-60));
	propTopR.setString("Vitesse de propagation");
	Element arrowLR(Texture("arrow.png"),sf::Vector2f((width/2)-300+45,(height/2)-20+47), 180.f);
	Element arrowRR(Texture("arrow.png"),sf::Vector2f((width/2)+250,(height/2)-20), 0.f);
	sf::Text proContR;
	proContR.setFont(Arial);
	proContR.setCharacterSize(30);
	proContR.setColor(sf::Color::Black);
	proContR.setPosition(sf::Vector2f((width/2)-30,(height/2)-10));
	proContR.setString(toString(valprop));

	//Reproduction
	sf::RectangleShape repR(sf::Vector2f(600,50));
	repR.setFillColor(sf::Color(0,0,0,50));
	repR.setPosition(sf::Vector2f((width/2)-300,(height/2)+80));
	sf::Text repTopR;
	repTopR.setFont(Arial);
	repTopR.setCharacterSize(30);
	repTopR.setColor(sf::Color::Black);
	repTopR.setPosition(sf::Vector2f((width/2)-230,(height/2)+40));
	repTopR.setString("Vitesse de reproduction");
	Element arrowLRe(Texture("arrow.png"),sf::Vector2f((width/2)-300+45,(height/2)+80+47), 180.f);
	Element arrowRRe(Texture("arrow.png"),sf::Vector2f((width/2)+250,(height/2)+80), 0.f);
	sf::Text reContR;
	reContR.setFont(Arial);
	reContR.setCharacterSize(30);
	reContR.setColor(sf::Color::Black);
	reContR.setPosition(sf::Vector2f((width/2)-30,(height/2)+90));
	reContR.setString(toString(valrepro));

	//Resistance
	sf::RectangleShape resR(sf::Vector2f(600,50));
	resR.setFillColor(sf::Color(0,0,0,50));
	resR.setPosition(sf::Vector2f((width/2)-300,(height/2)+180));
	sf::Text resTopR;
	resTopR.setFont(Arial);
	resTopR.setCharacterSize(30);
	resTopR.setColor(sf::Color::Black);
	resTopR.setPosition(sf::Vector2f((width/2)-100,(height/2)+140));
	resTopR.setString("Resistance");
	Element arrowLRes(Texture("arrow.png"),sf::Vector2f((width/2)-300+45,(height/2)+180+47), 180.f);
	Element arrowRRes(Texture("arrow.png"),sf::Vector2f((width/2)+250,(height/2)+180), 0.f);
	sf::Text resContR;
	resContR.setFont(Arial);
	resContR.setCharacterSize(30);
	resContR.setColor(sf::Color::Black);
	resContR.setPosition(sf::Vector2f((width/2)-30,(height/2)+190));
	resContR.setString(toString(valresis));

	//Point restant
	sf::RectangleShape restR(sf::Vector2f(295,50));
	restR.setFillColor(sf::Color(0,0,0,50));
	restR.setPosition(sf::Vector2f((width/2)-300,(height/2)+280));
	sf::Text restTopR;
	restTopR.setFont(Arial);
	restTopR.setCharacterSize(30);
	restTopR.setColor(sf::Color::Black);
	restTopR.setPosition(sf::Vector2f((width/2)-300,(height/2)+240));
	restTopR.setString("Points restant");
	sf::Text restContR;
	restContR.setFont(Arial);
	restContR.setCharacterSize(30);
	restContR.setColor(sf::Color::Black);
	restContR.setPosition(sf::Vector2f((width/2)-150,(height/2)+290));
	restContR.setString(toString(freepoints));

	//Valider
	sf::RectangleShape valR(sf::Vector2f(295,50));
	valR.setFillColor(sf::Color(0,0,0,50));
	valR.setPosition(sf::Vector2f((width/2)+5,(height/2)+280));
	sf::Text valTopR;
	valTopR.setFont(Arial);
	valTopR.setCharacterSize(30);
	valTopR.setColor(sf::Color::Black);
	valTopR.setPosition(sf::Vector2f((width/2)+80,(height/2)+280));
	valTopR.setString("Valider");

	unsigned int frame = 0;
	bool incColor=false;

	sf::Mouse mouse;
	sf::Event event;


	bool pressed=false;

	while (window->isOpen())
	{
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
			if (event.type == sf::Event::TextEntered){
				if(mouse.getPosition().x>(width/2)-150 && mouse.getPosition().x<(width/2)-150+450 && mouse.getPosition().y>(height/2)-200 && mouse.getPosition().y<(height/2)-200+50){
					if (event.text.unicode > 30 && event.text.unicode < 127){
						m_saisie += static_cast<char>(event.text.unicode);
						nomContR.setString(m_saisie);
					}
				}
			}
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Back)){
			if(m_saisie.length()>=1)
				m_saisie.resize(m_saisie.length()-1);
			nomContR.setString(m_saisie);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			if(!pauseMenu()){
				return false;
			}
		}


		if(mouse.getPosition().x>(width/2)-245 && mouse.getPosition().x<(width/2)-245+45 && mouse.getPosition().y>(height/2)-150 && mouse.getPosition().y<(height/2)-150+45){
			if(mouse.isButtonPressed(sf::Mouse::Left)&& !pressed){
				int actual =player->getStyle();
				actual++;
				if(actual==3)
					actual=0;
				player->setStyle(actual);
				layer2.clear();
				layer2.addElement(player->player);
				pressed=true;
			}
		}
		else if(mouse.getPosition().x>(width/2)-300 && mouse.getPosition().x<(width/2)-300+45 && mouse.getPosition().y>(height/2)-150 && mouse.getPosition().y<(height/2)-150+45){
			if(mouse.isButtonPressed(sf::Mouse::Left)&& !pressed){
				int actual =player->getStyle();
				actual--;
				if(actual==-1)
					actual=2;
				player->setStyle(actual);
				layer2.clear();
				layer2.addElement(player->player);
				pressed=true;
			}
		}
		else if(mouse.getPosition().x>(width/2)+250 && mouse.getPosition().x<(width/2)+250+45){
			if(mouse.getPosition().y>(height/2)-20 && mouse.getPosition().y<(height/2)-20+45){
				if(mouse.isButtonPressed(sf::Mouse::Left)&& !pressed && freepoints-1!=-1 &&valprop+1!=11){
					valprop++;
					freepoints--;
					proContR.setString(toString(valprop));
					restContR.setString(toString(freepoints));
					pressed=true;

				}
			}
			else if(mouse.getPosition().y>(height/2)+80 && mouse.getPosition().y<(height/2)+80+45){
				if(mouse.isButtonPressed(sf::Mouse::Left)&& !pressed && freepoints-1!=-1 &&valrepro+1!=11){
					valrepro++;
					freepoints--;
					reContR.setString(toString(valrepro));
					restContR.setString(toString(freepoints));
					pressed=true;

				}
			}
			else if(mouse.getPosition().y>(height/2)+180 && mouse.getPosition().y<(height/2)+180+45){
				if(mouse.isButtonPressed(sf::Mouse::Left)&& !pressed && freepoints-1!=-1 &&valresis+1!=11){
					valresis++;
					freepoints--;
					resContR.setString(toString(valresis));
					restContR.setString(toString(freepoints));
					pressed=true;

				}
			}
		}

		else if(mouse.getPosition().x>(width/2)-300 && mouse.getPosition().x<(width/2)-300+45){
			if(mouse.getPosition().y>(height/2)-20 && mouse.getPosition().y<(height/2)-20+45){
				if(mouse.isButtonPressed(sf::Mouse::Left)&& !pressed && freepoints+1!=18 &&valprop-1!=-1){
					valprop--;
					freepoints++;
					proContR.setString(toString(valprop));
					restContR.setString(toString(freepoints));
					pressed=true;

				}
			}
			else if(mouse.getPosition().y>(height/2)+80 && mouse.getPosition().y<(height/2)+80+45){
				if(mouse.isButtonPressed(sf::Mouse::Left)&& !pressed && freepoints+1!=18 &&valrepro-1!=-1){
					valrepro--;
					freepoints++;
					reContR.setString(toString(valrepro));
					restContR.setString(toString(freepoints));
					pressed=true;

				}
			}
			else if(mouse.getPosition().y>(height/2)+180 && mouse.getPosition().y<(height/2)+180+45){
				if(mouse.isButtonPressed(sf::Mouse::Left)&& !pressed && freepoints+1!=18 &&valresis-1!=-1){
					valresis--;
					freepoints++;
					resContR.setString(toString(valresis));
					restContR.setString(toString(freepoints));
					pressed=true;

				}
			}
		}
		if(mouse.getPosition().x>(width/2)+5 && mouse.getPosition().x<(width/2)+5+295 && mouse.getPosition().y>(height/2)+280 && mouse.getPosition().y<(height/2)+280+50){
			if(mouse.isButtonPressed(sf::Mouse::Left)&& !pressed){
				player->velocity=7+floor(valprop/3);
				player->resistance=valresis;
				return true;
			}
		}

		if(!mouse.isButtonPressed(sf::Mouse::Left))
			pressed=false;

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
		window->draw(frameR);
		window->draw(frameLR);
		arrowLF.draw(*window);
		window->draw(frameRR);
		arrowRF.draw(*window);

		window->draw(nomR);
		window->draw(nomTopR);
		window->draw(nomContR);

		window->draw(propR);
		window->draw(propTopR);
		arrowLR.draw(*window);
		arrowRR.draw(*window);
		window->draw(proContR);

		window->draw(repR);
		window->draw(repTopR);
		arrowLRe.draw(*window);
		arrowRRe.draw(*window);
		window->draw(reContR);

		window->draw(resR);
		window->draw(resTopR);
		arrowLRes.draw(*window);
		arrowRRes.draw(*window);
		window->draw(resContR);

		window->draw(restR);
		window->draw(restTopR);
		window->draw(restContR);

		window->draw(valR);
		window->draw(valTopR);

		layerManager.update(frame);
		layerManager.draw(*window);
		window->display();
		frame++;
	}

	return true;
}
