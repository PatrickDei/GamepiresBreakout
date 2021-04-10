#pragma once
#include "BreakpointObject.h"
#include <SFML/Audio.hpp>
#include "tinyxml2.h"
#include <iostream>

using namespace tinyxml2;

class Block : public BreakpointObject
{
protected:
	const char* _ID;
	const char* _soundPath;
	const char* _texturePath;
	const char* _breakPath;
	int _score;
	int _blockHealth;

	Block(const char* ID) : _ID(ID), BreakpointObject(0, 0, 25, 25) {
		_soundPath = getPathByAttributeName<const char*>("HitSound");
		_breakPath = getPathByAttributeName<const char*>("BreakSound");
		_texturePath = getPathByAttributeName<const char*>("Texture");
		_score = getPathByAttributeName<int>("BreakScore");
		_blockHealth = getPathByAttributeName<int>("HitPoints");
	}	
	
	virtual void loseHealth() = 0;	 

	void destroyBlock();

public:
	const char* getHitSoundPath();

	const char* getBreakSoundPath();

	virtual ~Block() {
		delete[] _ID;
		delete[] _soundPath;
		delete[] _breakPath;
		delete[] _texturePath;
	}

private:
	template<class T>
	T getPathByAttributeName(const char* attributeName) {
		XMLDocument profiles;
		profiles.LoadFile("Profiles/Items.xml");
		XMLElement* rootElement = profiles.RootElement();

		XMLElement* brickTypeElement = rootElement->FirstChildElement("BrickTypes");

		for (XMLElement* brickTypeChildElement = brickTypeElement->FirstChildElement("BrickType"); brickTypeChildElement != nullptr; brickTypeChildElement = brickTypeChildElement->NextSiblingElement())
		{
			if (strcmp(brickTypeChildElement->Attribute("Id"), _ID) == 0)
				return getAttribute<T>(brickTypeChildElement, attributeName);
		}
	}

	// template for getting proper attribute
	template<class T>
	T getAttribute(XMLElement* element, const char* attributeName) {
		return element->Attribute(attributeName);
	}

	//specialization
	template <>
	int getAttribute<int>(XMLElement* element, const char* attributeName) {
		return element->IntAttribute(attributeName);
	}
};

