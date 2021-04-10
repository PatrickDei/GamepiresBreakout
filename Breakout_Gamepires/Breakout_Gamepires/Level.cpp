#include "Level.h"

#define length(array) ((sizeof(array)) / (sizeof(array[0])))

std::vector<BreakpointObject*> Level::generateLevel(std::vector<char> characters)
{
	for (char c : characters)
		switch (c) {
		case 'S':
			_blocks.push_back(new SoftBlock());
			break;
		default:
			_blocks.push_back(new SoftBlock());
		}
	return _blocks;
}

std::vector<BreakpointObject*> Level::getObjectsForLevel(int levelID)
{
	XMLDocument profiles;
	profiles.LoadFile("Profiles/Items.xml");
	XMLElement* rootElement = profiles.RootElement();

	for (XMLElement* levelBricksElement = rootElement->FirstChildElement("Bricks"); levelBricksElement != nullptr; levelBricksElement = levelBricksElement->NextSiblingElement())
	{
		if (levelBricksElement->IntAttribute("levelId") == levelID) {
			std::vector<char> characters;
			const char* result = levelBricksElement->GetText();
			size_t size = strlen(result);
			for (size_t i = 0; i <  size - 1; i++)
				if (result[i] != ' ' && result[i] != '\t' && result[i] != '\n')
					characters.push_back(result[i]);
			return generateLevel(characters);
		}
	}
}
