#pragma once
#include "BreakpointObject.h"
#include <SFML/Audio.hpp>
#include "tinyxml2.h"
#include <iostream>

using namespace tinyxml2;

class Block : public BreakpointObject
{
protected:
	char _ID;
	std::string* _soundPath;
	std::string* _texturePath;
	std::string* _breakPath;
	int _score;
	int _blockHealth;

	Block(char ID) : _ID(ID), BreakpointObject(0, 0, 25, 25) {
		_soundPath = getPathByAttributeName<std::string*>("HitSound");
		_breakPath = getPathByAttributeName<std::string*>("BreakSound");
		_texturePath = getPathByAttributeName<std::string*>("Texture");
		if (ID != 'I') {
			_score = getPathByAttributeName<int>("BreakScore");
			_blockHealth = getPathByAttributeName<int>("HitPoints");
		}
		else {
			_score = 0;
			_blockHealth = 1;
		}
	}	
	
public:
	const char* getHitSoundPath();

	const char* getBreakSoundPath();

	const char* getTexturePath();

	// return true if no more health
	virtual bool loseHealth();	 

	int getScore();

	char getId();

	~Block() {
		delete _soundPath;
		delete _breakPath;
		delete _texturePath;
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
			if (brickTypeChildElement->Attribute("Id")[0] == _ID)
				return getAttribute<T>(brickTypeChildElement, attributeName);
		}
	}

	// template for getting proper attribute
	template<class T>
	T getAttribute(XMLElement* element, const char* attributeName) {
		for (const XMLAttribute* attributeOfElement = element->FirstAttribute(); attributeOfElement != nullptr; attributeOfElement = attributeOfElement->Next())
			if (strcmp(attributeOfElement->Name(), attributeName) == 0) {
				std::string* valueToReturn = new string(attributeOfElement->Value());
				return valueToReturn;
			}
	}

	//specialization
	template <>
	int getAttribute<int>(XMLElement* element, const char* attributeName) {
		return element->IntAttribute(attributeName);
	}
};

