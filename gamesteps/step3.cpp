#include "../gamestep.h"


class Cell : public Element
{
    typedef enum {BIG, MED, SMALL} Size;

    public:
        Cell(sf::Vector2f position, Size type, int startValue = 0) : Element(Texture("cellule.png"), position, 0.f)
        {
            value = startValue;
            setOrigin(250, 250);

            radius = (type==BIG ? 15 : (type==MED ? 10 : 5));

            //setSize(sf::Vector2f(radius,radius));
            genRate = (type==BIG ? 3 : (type==MED ? 2 : 1));

            valueText.setFont(Font("pixelart.ttf"));
            valueText.setOrigin(valueText.getLocalBounds().width/2.f, valueText.getLocalBounds().height/2.f);
            valueText.setString("99");
            valueText.setColor(sf::Color::White);
            update(0);

        }

        void update(int frame)
        {
            if(value > 0)
            {
                value += genRate;
            }
            if(value < 0)
            {
                value -= genRate;
            }

            valueText.setString(toString(value));
        }

        void draw(sf::RenderWindow &window)
        {
            //if(value > 0)

        }

        bool isInside(sf::Vector2f coord)
        {
            sf::Vector2f delta = coord - getPosition();
            float distance = sqrt(delta.x*delta.x + delta.y*delta.y);
            return distance < radius;
        }

    private:
        int value;
        int genRate;
        float radius;
        sf::Text valueText;

};


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
