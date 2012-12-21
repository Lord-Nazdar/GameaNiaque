#include "../gamestep.h"

class Cell : public Element
{
    public:
		typedef enum {BIG, MED, SMALL} Size;

        Cell(sf::Vector2f position, Size type, int startValue = 0) : Element(Texture("cellule.png"), position, 0.f)
        {
            value = startValue;
            setOrigin(250, 250);

            radius = (type==BIG ? 100 : (type==MED ? 75 : 50));

            float scale = 2.f*radius/sprite.getLocalBounds().width;
            setScale(scale, scale);


            genRate = (type==BIG ? 3 : (type==MED ? 2 : 1));

            valueText.setFont(Font("pixelart.ttf"));
            valueText.setCharacterSize(24);
            valueText.setString("00");
            valueText.setOrigin(valueText.getGlobalBounds().width/2.f, valueText.getGlobalBounds().height/2.f);
            valueText.setPosition(position);
            valueText.setColor(sf::Color::White);

			setColor(sf::Color(200,200,200));

			lastAttack = 0;
        }

        void update(int frame)
        {
			if(frame % (60/genRate) == 0)
        	{
				if(value > 0) value ++;
				if(value < 0) value --;

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

			std::string v = toString(abs(value));
			if(v.length() < 2) v = '0' + v;
            valueText.setString(v);

            window.draw(valueText);


        }

        bool isInside(sf::Vector2i coord)
        {
            sf::Vector2f delta = sf::Vector2f(coord.x, coord.y) - getPosition();
            float distance = sqrt(delta.x*delta.x + delta.y*delta.y);
            return (distance < radius);
        }

        float getRadius() {	return radius; }

        int getValue() { return value; }

        int sendValue(int v)
        {
        	if(value < -v)
        	{
				value += v;
				return -v;
        	}
			else
			if(value < 0)
			{
				v = value+1;
				value = -1;
				return v;
			}
			else
			if(value > v)
			{
				value -= v;
				return v;
			}
			else
			if(value > 0)
			{
				v = value-1;
				value = 1;
				return v;
			}
			else
			if(value == 0)
			{
				return 0;
			}
        }

        void receiveValue(int v)
        {
        	value += v;
			if(value < -99) value = -99;
            if(value > 99) value = 99;
        }

        float getAICost(Cell* c)
        {
			float cost = -1.f;

			sf::Vector2f delta = c->getPosition() - getPosition();
			float distance = sqrt( delta.x*delta.x + delta.y*delta.y );
			float value = c->getValue();
			int size = c->getRadius();

			if(value >= 0)
				cost = size * (100-value) * (1/distance);

			return cost;
        }

        int getLastAttack() {return lastAttack;}
        void setLastAttack(int a) {lastAttack = a;}

    private:
        int value; // Amount of agents in the cell. Positive number means allies agents (virus), Negative number means enemy agents (leucocytes)
        int genRate;
        float radius;
        sf::Text valueText;
        int lastAttack;

};


class Agent : public AnimatedElement
{
	public:

	Agent(int v, Cell& c1, Cell& c2, float speed = 1.f) : AnimatedElement(Texture("grid.png"), sf::Vector2f(), 0.f, 64, 1, GameStep::player->getStyle()*8 ), c2(c2)
		{
			setOrigin(32, 32);
			setScale(.5f, .5f);

			delta = c2.getPosition() - c1.getPosition();
			float length = sqrt( delta.x * delta.x + delta.y * delta.y );
			delta /= length;

			sf::Vector2f startPos = c1.getPosition() + delta*c1.getRadius();
			sf::Vector2f endPos = c2.getPosition() - delta*c2.getRadius();
			setPosition(startPos);

			sf::Vector2f travel = endPos - startPos;
			length = sqrt( travel.x*travel.x + travel.y*travel.y );

			value = c1.sendValue(v);

			//speed *= (value < 0 ? 1.f : .5f);
			delta *= speed;

			duration = length/speed;
			elapsed = 0;

			if(value != 0) alive = true; else setColor(sf::Color::Transparent);
			if(value < 0) sprite.setTextureRect(sf::IntRect(0, 196, 64, 64));

		}

		void update(int frame)
		{
			if(value > 0 && frame%20 == 0)
			{
				setFrame(frameIndex);
				frameIndex++;
			}

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

namespace AI
{
	class SortFunctor
	{
		public:
			SortFunctor(Cell* c) : c0(c) { }

			bool operator()(Cell* c1, Cell* c2)
			{ return (c0->getAICost(c1) > -1.f) && c0->getAICost(c1) > c0->getAICost(c2); }

		private:
			Cell* c0;
	};

	class RemoveFunctor
	{
		public:
			RemoveFunctor(Cell* c) : c0(c) { }

			bool operator()(Cell* c)
			{ return c0->getAICost(c) < 0.f; }

		private:
			Cell* c0;
	};
}

class Gamestep3
{
	public:
		Gamestep3(sf::RenderWindow& window) :
			window(window),
			layerAgent(2,0),
			layerCell(1,0),
			layerBackground(0,1),
			frame(0),
			selectedCell(NULL),
			reticule(Texture("reticule.png")),
			win(false),
			lose(false)
		{}

		void init();
		void update();
		void onclick(Cell* c, bool lbutton);
		void select(Cell* c);
		void unselect();

		bool win;
		bool lose;

	private:

		sf::RenderWindow& window;

		LayerManager layerManager;
		Layer layerAgent;
		Layer layerCell;
		Layer layerBackground;
		Layer white1l;
		Layer white2l;

		std::vector<Element*> white1;
		std::vector<Element*> white2;

		std::vector<Cell*> cells;
		std::vector<Agent*> agents;

		bool clicked;
		Cell* selectedCell;
		Element reticule;

		int frame;
};

bool GameStep::step3()
{
	srand(time(NULL));
	int frame=0;

	sf::Music menuMusic;
	//logoMusic=new sf::Music("logo.wav");
	menuMusic.openFromFile("music/part3.wav");
	menuMusic.play();
	menuMusic.setLoop(true);

	Gamestep3 gm3(*window);
	gm3.init();

	while (window->isOpen() && !gm3.win && !gm3.lose)
	{
		stepEvent();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			if(!pauseMenu()){
				return false;
			}
		}
		//Supprimer imp�rativement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)){
			gm3.win=true;
		}
		gm3.update();
		frame++;
	}
	if(!gm3.lose){
		score+=7500-frame;
		if(score<0)
			score=0;
	}

	return true;

}

void Gamestep3::select(Cell* c)
{
	c->setColor(sf::Color(255,255,255));
	selectedCell = c;
}

void Gamestep3::unselect()
{
	if(selectedCell)
		selectedCell->setColor(sf::Color(200, 200, 200));
	selectedCell = NULL;
}

void Gamestep3::init()
{
	window.setMouseCursorVisible(true);

	layerManager.add(&white1l);
	layerManager.add(&white2l);

	layerManager.add(&layerBackground);
	layerManager.add(&layerCell);
	layerManager.add(&layerAgent);


	// Generation de la map de cellules
	const sf::Vector2u viewport = window.getSize();
	const sf::Vector2u margins(100, 100);

	const int maxRadius = 50;
	const int minSpacing = 5;

	const int idealCols = 10;
	const int idealRows = 5;

	int W = viewport.x - 2 * ( margins.x + maxRadius );
	int H = viewport.y - 2 * ( margins.y + maxRadius );

	int U = H / (( maxRadius + minSpacing ) * 4);
	int V = W / (( maxRadius + minSpacing ) * 2);

	if(U > idealRows) U = idealRows;
	if(V > idealCols) V = idealCols;

	float dx = W / (V - 1);
	float dy = H / (U * 1.5f);

	for(int u = 0; u < U; u++)
	{
		for(int v = 0; v < V; v++)
		{

			float x = v 			* dx + margins.x + maxRadius;
			float y = (u*2 + v%2) 	* dy + margins.y + maxRadius;


			Cell::Size s;
			switch(rand() % 3)
			{
				case 0: s = Cell::SMALL; break;
				case 1: s = Cell::MED; break;
				case 2: s = Cell::BIG; break;
			}


			Cell* c;

			if(u == 0 && v == 0) // Le joueur commence dans le coin haut gauche
				c = new Cell(sf::Vector2f(x, y), Cell::BIG, 1);
			else if(u == U-1 && v == V-1) // Et l'ennemi dans le coin bas droite
				c = new Cell(sf::Vector2f(x, y), Cell::BIG, -1);
			else
				c = new Cell(sf::Vector2f(x, y), s);


			cells.push_back(c);
			layerCell.addElement(c);

		}
	}


	reticule.setOrigin(64, 64);
	layerCell.addElement(&reticule);

}

void Gamestep3::update()
{
	int width= window.getSize().x;
	int height= window.getSize().y;

	int white1size = white1.size();
	int white2size = white2.size();

	for(unsigned int j=0; j<white1size; j++){
		if(white1size>0 && white1.at(j)->getPosition().y>height+128){
			white1.erase(white1.begin()+j);
			white1size--;
		}
	}

	for(unsigned int j=0; j<white2size; j++){
		if(white2size>0 && white2.at(j)->getPosition().y>height+128){
			white2.erase(white2.begin()+j);
			white2size--;
		}
	}


	//spawn white1
	if(frame%30==0){
		int r = 0 + (rand() % ((width-128) - 0));
		white1.push_back(new Element(Texture("white1.png"),sf::Vector2f(r,0), 0.f));
		float srand = (rand()%5)/10.0;
		white1[white1.size()-1]->setScale(0.75+(srand),0.75+(srand));
		white1l.addElement(white1[white1.size()-1]);
	}

	//spawn white2
	if(frame%50==0){
		int r = 0 + (rand() % ((width-128) - 0));
		white2.push_back(new Element(Texture("white2.png"),sf::Vector2f(r,0), 0.f));
		float srand = (rand()%10)/10.0;
		white2[white2.size()-1]->setScale(0.75+(srand),0.75+(srand));
		white2l.addElement(white2[white2.size()-1]);
	}
	//Update white1
	for(std::vector<Element*>::iterator i = white1.begin(); i != white1.end(); i++){
		(*i)->move(0,2);
	}

	//Update white2
	for(std::vector<Element*>::iterator i = white2.begin(); i != white2.end(); i++){
		(*i)->move(0,1);
	}


	// Gestion du click
	bool lbutton = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	bool rbutton = sf::Mouse::isButtonPressed(sf::Mouse::Right);

	if( (lbutton || rbutton) && !clicked)
	{
		clicked = true;
		bool clicDansLeVide = true;

		for(std::vector<Cell*>::iterator i = cells.begin(); i != cells.end(); i++)
		{
			if( (*i)->isInside(sf::Mouse::getPosition()) )
			{
				onclick(*i, lbutton);
				clicDansLeVide = false;
				break;
			}
		}

		if(lbutton && clicDansLeVide) unselect();
	}

	if(!lbutton && !rbutton) clicked = false;






	// Dessin du réticule pour la cellule selectionnée
	if(selectedCell != NULL)
	{
		reticule.setColor(sf::Color::Green);
		reticule.setPosition(selectedCell->getPosition());
		reticule.rotate(2);
		float scale = (100+abs(((frame/4)%40)-20)) / 100.f;
		reticule.setScale( scale * selectedCell->getScale() * 5.f );
	}
	else
	{
		reticule.setColor(sf::Color::Transparent);
	}


	// Suppression des agents inactifs
	for(std::vector<Agent*>::iterator i = agents.begin(); i != agents.end();)
	{
		if( !(*i)->isAlive() )
		{
			delete (*i);
			layerAgent.removeElement(*i);
			i = agents.erase(i);
		}
		else i++;
	}



	// Conditions de victoire et pre-check pour l'AI
	int nbPositive = 0;
	int nbNegative = 0;
	int nbNeutre = 0;
	for(std::vector<Cell*>::iterator i = cells.begin(); i != cells.end(); i++)
	{
		if( (*i)->getValue() > 0 ) nbPositive++;
		if( (*i)->getValue() < 0 ) nbNegative++;
		if( (*i)->getValue() == 0 ) nbNeutre++;
	}
	if(nbPositive == 0) lose = true;
	if(nbNegative == 0) win = true;


	// Boucle AI
	for(std::vector<Cell*>::iterator i = cells.begin(); i != cells.end(); i++)
	{
		if( (*i)->getValue() < 0 )
		{
			int intervalBetweenAttacks = ((120 /*+ rand()%60*/) /*- (*i)->getValue()*3*/ + nbNegative*50);

			if((*i)->getLastAttack() == 0) (*i)->setLastAttack(frame);
			if(frame - (*i)->getLastAttack() > intervalBetweenAttacks)
			{
				(*i)->setLastAttack(frame);

				// Opérations très lourdes mais osef total vu les perfs du jeu
				std::vector<Cell*> targets = cells;
				std::sort(targets.begin(), targets.end(), AI::SortFunctor((*i)));
				std::remove_if(targets.begin(), targets.end(), AI::RemoveFunctor((*i)));

				if(targets.size() > 0)
				{
					int target = rand() % min(3, (int)targets.size());

					Agent* a = new Agent(10, *(*i), *(targets[target]));
					agents.push_back(a);
					layerAgent.addElement(a);
				}
			}

		}
	}

	// Fond rouge
	int red = 90+abs(((frame/4)%60)-30);
	window.clear(sf::Color(red, 22, 22));


	layerManager.update(frame);
	layerManager.draw(window);
	window.display();

	frame++;
}

void Gamestep3::onclick(Cell* c, bool lbutton)
{
	if(lbutton)
	{
		if(c->getValue() > 0)
		{
			unselect();
			select(c);
		}
	}
	else if(selectedCell != NULL)
	{
		Agent* a = new Agent(10, *selectedCell, *c);
		agents.push_back(a);
		layerAgent.addElement(a);
	}
}
