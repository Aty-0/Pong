//===================Config.h========================
// Purpose:		Game config's
// Readiness:   Beta
//=================================================

#pragma once
#include "Game.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class CConfig
{
public:
	XMLDocument xmldoc;
	XMLError eResult;
	XMLNode *pRoot;
	XMLElement *pElement;
	//Read config and launch commands
	bool LoadConfig(const char *Path, const char *NameElement);
	//If need set float value
	bool LoadConfig(const char *Path, const char *NameElement, float &Value);
	//If need set int value
	bool LoadConfig(const char *Path, const char *NameElement, int &Value);
	//If need set text
	bool LoadConfig(const char *Path, const char *NameElement, string &Text);
	//If need set bool
	bool LoadConfig(const char *Path, const char *NameElement, bool &State);
	//If need set Color
	bool LoadConfig(const char *Path, Color &color);
};

extern CConfig *config;
