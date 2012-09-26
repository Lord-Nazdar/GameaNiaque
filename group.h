#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include <SFML/Graphics.hpp>

namespace sf
{

    //template <typename T>
	class Group : public Drawable, public std::vector<Drawable*>, public Transformable{
        public:
            Group() :
                Drawable(),
                std::vector<Drawable*>()
			{ }

			~Group(){
				for(std::vector<Drawable*>::iterator i = begin(); i != end(); ++i){
                    delete *i;
                }
            }

            virtual void draw(RenderTarget& target, RenderStates states) const{
                for(std::vector<Drawable*>::const_iterator i = begin(); i != end(); ++i){
                    target.draw(**i, states);
                }
            }
    };

    //typedef Group<Drawable> Node;

}

#endif // GROUP_H
