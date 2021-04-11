#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "tinyxml2.h"

class TextureController
{
private:
	std::map<char, sf::Texture> _textureMap;

public:
	TextureController() {
		tinyxml2::XMLDocument profiles;
		profiles.LoadFile("Profiles/Items.xml");
		tinyxml2::XMLElement* rootElement = profiles.RootElement();

		tinyxml2::XMLElement* brickTypeElement = rootElement->FirstChildElement("BrickTypes");

		for (tinyxml2::XMLElement* brickTypeChildElement = brickTypeElement->FirstChildElement("BrickType"); brickTypeChildElement != nullptr; brickTypeChildElement = brickTypeChildElement->NextSiblingElement())
		{
			sf::Texture t;
			t.loadFromFile(brickTypeChildElement->Attribute("Texture"));
			_textureMap.insert(std::pair<char, sf::Texture>(brickTypeChildElement->Attribute("Id")[0], t));
		}
	}

	sf::Texture getTextureForId(char Id);
};