#ifndef LAYER_H
#define LAYER_H

#include <SFML/Graphics.hpp>
#include <vector>

class Layer
{
public:
	Layer();
	Layer(int PZIndex, float PParalaxSpeed);

	int getZIndex();
	void setBackgroundColor(sf::Color color);
	void draw(sf::RenderWindow &window, sf::RenderStates states) const;
	void move(float speed, int direction);
	void addSprite(sf::Sprite *sprite);

private:
	int ZIndex;
	float parallaxSpeed;
	std::vector<sf::Sprite*> spriteVector;
};

#endif // LAYER_H
