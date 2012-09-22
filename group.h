#ifndef GROUP_H
#define GROUP_H

#include <SFML/Graphics.hpp>

class Group : public sf::Drawable, public std::vector<sf::Drawable*> {
	public:
		Group();
		~Group();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // GROUP_H
