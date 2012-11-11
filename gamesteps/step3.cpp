#include "../gamestep.h"


class Cell : public Element
{
    public:
		typedef enum {BIG, MED, SMALL} Size;

        Cell(sf::Vector2f position, Size type, int startValue = 0) : Element(Texture("cellule.png"), position, 0.f)
        {
            value = startValue;
            setOrigin(250, 250);

            radius = (type==BIG ? 200 : (type==MED ? 150 : 100));

            float scale = radius/sprite.getLocalBounds().width;
            setScale(scale, scale);


            genRate = (type==BIG ? 3 : (type==MED ? 2 : 1));

            valueText.setFont(Font("pixelart.ttf"));
            valueText.setString("00");
            valueText.setOrigin(valueText.getLocalBounds().width/2.f, valueText.getLocalBounds().height/2.f);
            valueText.setPosition(position);
            valueText.setColor(sf::Color::White);
            update(0);

        }

        void update(int frame)
        {
        	if(frame%30 == 0)
        	{
				if(value > 0)
				{
					value += genRate;
				}
				if(value < 0)
				{
					value -= genRate;
				}

				if(value < -99) value = -99;
				if(value > 99) value = 99;
        	}
        }

        void draw(sf::RenderWindow &window)
        {
            Element::draw(window);

			if(value > 0)
            {
                valueText.setColor(sf::Color(87,0,127));
            }
            if(value < 0)
            {
                valueText.setColor(sf::Color::White);
            }
            if(value == 0)
            {
            	valueText.setColor(sf::Color(127, 0, 0));
            }

            valueText.setString(toString(abs(value)));
            window.draw(valueText);


        }

        bool isInside(sf::Vector2i coord)
        {
            sf::Vector2f delta = sf::Vector2f(coord.x, coord.y) - getPosition();
            float distance = sqrt(delta.x*delta.x + delta.y*delta.y);
            return (distance < radius/2);
        }

        float getRadius() {	return radius; }

        int getValue() { return value; }

        int sendValue(int v)
        {
			if(abs(value) < abs(v))
			{
				int t = value;
				value = 0;
				return t;
			}
			else
			{
				value -= v;
				return v;
			}
        }

        void receiveValue(int v)
        {
        	value += v;
			if(value < -99) value = -99;
            if(value > 99) value = 99;
        }

    private:
        int value;
        int genRate;
        float radius;
        sf::Text valueText;

};

class Agent : public Element
{
	public:

		Agent(int value, Cell& c1, Cell& c2, float speed = 1.f) : Element( (value > 0 ? Texture("cellule.png") : Texture()) ), c2(c2)
		{
			delta = c2.getPosition() - c1.getPosition();
			float length = sqrt( delta.x * delta.x + delta.y * delta.y );
			delta /= length;

			sf::Vector2f startPos = c1.getPosition() + delta*c1.getRadius();
			sf::Vector2f endPos = c2.getPosition() - delta*c2.getRadius();
			setPosition(startPos);

			delta *= speed;

			duration = length/speed;
			elapsed = 0;

			value = c1.sendValue(value);
			alive = true;

		}

		void update(int frame)
		{
			if(alive)
				if(elapsed < duration)
				{
					move(delta);
					elapsed++;
				}
				else
				{
					c2.receiveValue(value);
					alive = false;
				}
		}

		bool isAlive(){ return alive; }

	private:
		int value;
		Cell& c2;
		bool alive;

		sf::Vector2f delta;
		int duration;
		int elapsed;

};


bool GameStep::step3(){

	window->setMouseCursorVisible(true);

	int red=120;
	bool incColor=false;

	LayerManager layerManager;

	Layer layerA(2,0);	//Agent layer
	Layer layerC(1,0);	//Cell layer
	Layer layerB(0,1);	//Background

	layerManager.add(&layerB);
	layerManager.add(&layerC);
	layerManager.add(&layerA);

	std::vector<Cell*> cells;
	std::vector<Agent*> agents;

	Cell* c1 = new Cell(sf::Vector2f(100.f, 100.f), Cell::MED, 0);
	Cell* c2 = new Cell(sf::Vector2f(300.f, 100.f), Cell::SMALL, 30);
	Cell* c3 = new Cell(sf::Vector2f(100.f, 300.f), Cell::BIG, -30);

	cells.push_back(c1);
	cells.push_back(c2);
	cells.push_back(c3);

	layerC.addElement(c1);
	layerC.addElement(c2);
	layerC.addElement(c3);


	while (window->isOpen())
	{
		stepEvent();

		if(mouseButtonDown){

			for(std::vector<Cell*>::iterator i = cells.begin(); i != cells.end(); i++)
			{
				if( (*i)->isInside(sf::Mouse::getPosition()) )
				{
					(*i)->setColor(sf::Color::Blue);
				}
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


		window->clear(sf::Color(red,22,22));
		layerManager.update(frame);
		layerManager.draw(*window);
		window->display();

		frame++;
	}
}
