#include "Level.h"

std::vector<BreakpointObject*> Level::generateLevel(std::vector<char> characters)
{
	_blocks.clear();
	for (char c : characters)
		switch (c) {
		case 'S':
			_blocks.push_back(new SoftBlock());
			break;
		case 'M':
			_blocks.push_back(new MediumBlock());
			break;
		case 'H':
			_blocks.push_back(new HardBlock());
			break;
		case 'I':
			_blocks.push_back(new ImpenetrableBlock());
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