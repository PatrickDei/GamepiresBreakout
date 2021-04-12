#pragma once
#include "BreakpointObject.h"
#include "tinyxml2.h"
#include <string>

using namespace tinyxml2;

/// <summary>
/// Block base class inherited by different block types
/// </summary>
class Block : public BreakpointObject
{
protected:
	char _ID;
	std::string* _soundPath;
	std::string* _breakPath;
	int _score;
	int _blockHealth;

	Block(char ID) : _ID(ID), BreakpointObject(0, 0, 25, 25) {
		_soundPath = getAttributeByName<std::string*>("HitSound");
		_breakPath = getAttributeByName<std::string*>("BreakSound");
		try{
			_score = getAttributeByName<int>("BreakScore");
			_blockHealth = getAttributeByName<int>("HitPoints");
		}
		catch (...) {
			// caught if no attribute is found (Impenetrable block)
			_score = 0;
			_blockHealth = 1;
		}
	}	
	
public:
	int getScore();

	char getId();

	const char* getHitSoundPath();

	const char* getBreakSoundPath();

	/// Return true if no more health
	virtual bool loseHealth();	 

	~Block() {
		delete _soundPath;
		delete _breakPath;
	}

private:
	/// <summary>
	/// Returns value from xml document based on attribute and block ID
	/// </summary>
	/// <typeparam name="T"> Determines attribute type to be stored </typeparam>
	/// <param name="attributeName"> Attribute that is being searched for </param>
	/// <returns> Value of assigned attribute </returns>
	template<class T>
	T getAttributeByName(const char* attributeName) {
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

	/// <summary>
	/// Template for desired attribute
	/// </summary>
	/// <typeparam name="T"> Determines attribute type </typeparam>
	/// <param name="element"> Element to find attribute in (was found by ID) </param>
	/// <param name="attributeName"> Attribute we are searching for </param>
	/// <returns> String* for desired attribute </returns>
	template<class T>
	T getAttribute(XMLElement* element, const char* attributeName) {
		for (const XMLAttribute* attributeOfElement = element->FirstAttribute(); attributeOfElement != nullptr; attributeOfElement = attributeOfElement->Next())
			if (strcmp(attributeOfElement->Name(), attributeName) == 0) {
				std::string* valueToReturn = new std::string(attributeOfElement->Value());
				return valueToReturn;
			}
	}

	/// <summary>
	/// Specialization for int type
	/// </summary>
	/// <param name="element"> Element to find attribute in (was found by ID) </param>
	/// <param name="attributeName"> Attribute we are searching for </param>
	/// <returns> int for desired attribute </returns>
	template <>
	int getAttribute<int>(XMLElement* element, const char* attributeName) {
		return element->IntAttribute(attributeName);
	}
};

