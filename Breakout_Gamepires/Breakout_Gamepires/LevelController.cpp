#include "LevelController.h"

void LevelController::adjustBlockWidth(std::vector<BreakpointObject*>& objects, int gap, int columnCount, int columnSpacing)
{
	int blockWidth = (windowWidth - 2 * gap - columnCount * columnSpacing) / columnCount;
	for (BreakpointObject* object : objects)
		object->setWidth(blockWidth);
}

std::vector<BreakpointObject*> LevelController::loadBlocksForNextLevel()
{
    vector<BreakpointObject*> blocks = _levelLoader.getObjectsForLevel(_currentLevel++);

	XMLDocument profiles;
	profiles.LoadFile("Profiles/Items.xml");
	XMLElement* rootElement = profiles.RootElement();

	int rowCount = rootElement->IntAttribute("RowCount");
	int columnCount = rootElement->IntAttribute("ColumnCount");

	int rowSpacing = rootElement->IntAttribute("RowSpacing");
	int columnSpacing = rootElement->IntAttribute("ColumnSpacing");

	//int gapToLeft = (windowWidth - rowCount * (rowSpacing + blocks.front()->getWidth())) / 2;
	int gapToLeft = 100;
	int gapToTop = 100;

	adjustBlockWidth(blocks, gapToLeft, columnCount, columnSpacing);

	for (int i = 0; i < blocks.size(); i++)
		blocks[i]->setPosition(gapToLeft + i * (blocks.front()->getWidth() + columnSpacing) - (i / columnCount) * (columnCount * (columnSpacing + blocks.front()->getWidth())), 
			gapToTop + (rowSpacing + blocks.front()->getHeight()) * (i / columnCount + 1));

	return blocks;
}