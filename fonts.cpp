#include "fonts.h"

sf::Font& Font(std::string a_fileName)
{
    static std::map<std::string, sf::Font> fonts;

    if(fonts.count(a_fileName) == 0)
		std::cout << "Loaded : " << a_fileName << " : " << fonts[a_fileName].loadFromFile(a_fileName) << std::endl;

    return fonts[a_fileName];
}
