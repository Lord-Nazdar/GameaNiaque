#include "textures.h"

sf::Texture& Texture(std::string a_fileName)
{
    static std::map<std::string, sf::Texture> textures;

    if(textures.count(a_fileName) == 0)
		std::cout << "Loaded : " << a_fileName << " : " << textures[a_fileName].loadFromFile("images/" + a_fileName) << std::endl;

    return textures[a_fileName];
}
