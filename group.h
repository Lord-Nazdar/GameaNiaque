#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

namespace sf
{

    //template <typename T>
	class Group : public sf::Sprite, public std::vector<Sprite*>{
        public:
			Group() : Sprite(), std::vector<Sprite*>(){
			}

			~Group(){
				for(std::vector<Sprite*>::iterator i = begin(); i != end(); ++i){
                    delete *i;
                }
            }

			virtual void draw(RenderTarget& target, sf::RenderStates states) const{
				for(std::vector<Sprite*>::const_iterator i = begin(); i != end(); ++i){
                    target.draw(**i, states);
                }
            }

    };

	//typedef Group<Sprite> Node;

}

#endif // GROUP_H
