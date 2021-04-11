#include "TextureController.h"

sf::Texture TextureController::getTextureForId(char Id)
{
    return _textureMap.at(Id);
}
