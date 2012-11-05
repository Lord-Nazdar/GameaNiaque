#ifndef ANIMATEDELEMENT_H
#define ANIMATEDELEMENT_H

#include "SFML/Graphics.hpp"
#include <string>
#include "element.h"

class AnimatedElement : public Element
{
public:
	AnimatedElement();
	AnimatedElement(sf::Texture& pTex, sf::Vector2f pPos, float pOrientation, int frameSize, int maxFrames, int pstartframe);


	virtual void draw(sf::RenderWindow &window);
	virtual void update(int frame);
	void setFrame(int frame);

protected:
	int frameSize;
	int maxFrames;
	int frameIndex;
	int startframe;

};

#endif // ANIMATEDELEMENT_H

