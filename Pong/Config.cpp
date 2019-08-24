//===================Config.cpp====================
// Purpose:		Game config's
// Readiness:   Beta
//=================================================

#include "Config.h"

//Commands
bool CConfig::LoadConfig(const char *Path, const char *NameElement)
{
	return 1;
}

//Set Float Value
bool CConfig::LoadConfig(const char *Path, const char *NameElement, float &Value)
{
	logger->Print("Load config " + string(Path), logger->Debug);

	//Try Load file
	eResult = xmldoc.LoadFile(Path);
	//Check on Error
	if (!eResult == XMLError::XML_SUCCESS)
	{
		logger->Print("Can't load config | eResult = " + to_string(eResult), logger->FatalError);
		return 0;
	}

	//Read first child
	pRoot = xmldoc.FirstChild();
	if (pRoot == nullptr)
	{
		logger->Print("File read pRoot error", logger->FatalError);
		return 0;
	}

	//Read element
	pElement = pRoot->FirstChildElement(NameElement);
	if (pElement == nullptr)
	{
		logger->Print("File read Element error | Name Element = " + string(NameElement), logger->FatalError);
		return 0;
	}
	else
	{
		//Set Element
		eResult = pElement->QueryFloatText(&Value);
		//Check on Error
		if (!eResult == XMLError::XML_SUCCESS)
		{
			logger->Print("Can't set float value | eResult = " + to_string(eResult), logger->FatalError);
			return 0;
		}
	}
	return 1;
}

//Set Int Value
bool CConfig::LoadConfig(const char *Path, const char *NameElement, int &Value)
{
	logger->Print("Load config " + string(Path), logger->Debug);

	//Try Load file
	eResult = xmldoc.LoadFile(Path);
	//Check on Error
	if (!eResult == XMLError::XML_SUCCESS)
	{
		logger->Print("Can't load config | eResult = " + to_string(eResult), logger->FatalError);
		return 0;
	}

	//Read first child
	pRoot = xmldoc.FirstChild();
	if (pRoot == nullptr)
	{
		logger->Print("File read pRoot error", logger->FatalError);
		return 0;
	}

	//Read element
	pElement = pRoot->FirstChildElement(NameElement);
	if (pElement == nullptr)
	{
		logger->Print("File read Element error | Name Element = " + string(NameElement), logger->FatalError);
		return 0;
	}
	else
	{
		//Set Element
		eResult = pElement->QueryIntText(&Value);
		//Check on Error
		if (!eResult == XMLError::XML_SUCCESS)
		{
			logger->Print("Can't set int value | eResult = " + to_string(eResult), logger->FatalError);
			return 0;
		}
	}
	return 1;
}

//Set String Value
bool CConfig::LoadConfig(const char *Path, const char *NameElement, string &Text)
{
	return 1;
}

//Set Bool State
bool CConfig::LoadConfig(const char *Path, const char *NameElement, bool &State)
{
	logger->Print("Load config " + string(Path), logger->Debug);

	//Try Load file
	eResult = xmldoc.LoadFile(Path);
	//Check on Error
	if (!eResult == XMLError::XML_SUCCESS)
	{
		logger->Print("Can't load config | eResult = " + to_string(eResult), logger->FatalError);
		return 0;
	}

	//Read first child
	pRoot = xmldoc.FirstChild();
	if (pRoot == nullptr)
	{
		logger->Print("File read pRoot error", logger->FatalError);
		return 0;
	}

	//Read element
	pElement = pRoot->FirstChildElement(NameElement);
	if (pElement == nullptr)
	{
		logger->Print("File read Element error | Name Element = " + string(NameElement), logger->FatalError);
		return 0;
	}
	else
	{
		//Set Element
		eResult = pElement->QueryBoolText(&State);
		//Check on Error
		if (!eResult == XMLError::XML_SUCCESS)
		{
			logger->Print("Can't set bool | eResult = " + to_string(eResult), logger->FatalError);
			return 0;
		}
	}
	return 1;
}

//Set Color
bool CConfig::LoadConfig(const char *Path, Color &color)
{
	logger->Print("Load config " + string(Path), logger->Debug);

	//Try Load file
	eResult = xmldoc.LoadFile(Path);
	//Check on Error
	if (!eResult == XMLError::XML_SUCCESS)
	{
		logger->Print("Can't load config | eResult = " + to_string(eResult), logger->FatalError);
		return 0;
	}

	//Read first child
	pRoot = xmldoc.FirstChild();
	if (pRoot == nullptr)
	{
		logger->Print("File read pRoot error", logger->FatalError);
		return 0;
	}

	int _r;
	int _g;
	int _b;
	//Read r
	pElement = pRoot->FirstChildElement("R");
	if (pElement == nullptr)
		return 0;
	//Set Element
	eResult = pElement->QueryIntText(&_r);
	//Check on Error
	if (!eResult == XMLError::XML_SUCCESS)
		return 0;
	//Read g
	pElement = pRoot->FirstChildElement("G");
	if (pElement == nullptr)
		return 0;
	//Set Element
	eResult = pElement->QueryIntText(&_g);
	//Check on Error
	if (!eResult == XMLError::XML_SUCCESS)
		return 0;
	//Read b
	pElement = pRoot->FirstChildElement("B");
	if (pElement == nullptr)
		return 0;
	//Set Element
	eResult = pElement->QueryIntText(&_b);
	//Check on Error
	if (!eResult == XMLError::XML_SUCCESS)
		return 0;
	
	//Set Color 
	color = Color(_r, _g, _b);
	//Clear rgb
	_r = 0;
	_g = 0;
	_b = 0;
	logger->Print("r = " + to_string(color.r) + " g = " + to_string(color.g) + " b = " + to_string(color.b), logger->Debug);
	return 1;
}