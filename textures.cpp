#include "textures.h"

sf::Texture& Texture(std::string a_fileName)
{
    static std::map<std::string, sf::Texture> textures;

    if(textures.count(a_fileName) == 0)
        std::cout << textures[a_fileName].loadFromFile("" + a_fileName) << std::endl;

    std::cout << a_fileName << std::endl;
    std::cout << "Loaded : " << (textures.count(a_fileName)) << std::endl;

    return textures[a_fileName];
}
