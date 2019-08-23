//===================macros.h==========================
// Purpose:			Macroses
//
//=====================================================

#pragma once
#include "SFML/Graphics.hpp"
#include "Logger.h"

#define LOAD_FONT(p,s) { if(!p.loadFromFile(s)) { logger->Print("Can't load font, Maybe file is not exist", logger->FatalError); } }
#define LOAD_TEXTURE(p,s) { if(!p.loadFromFile(s)) { logger->Print("Can't load texture, Maybe file is not exist", logger->FatalError); } }
#define LOAD_IMAGE(p,s) { if(!p.loadFromFile(s)) { logger->Print("Can't load image, Maybe file is not exist", logger->FatalError); } }
#define LOAD_FROM_IMAGE(p,s) { if(!p.loadFromImage(s)) { logger->Print("Can't load from image", logger->FatalError); } }
#define SAFE_DELETE(p) { if(p) { delete (p); (p) = NULL; } }
#define CREATE_TEXT(text, size, font, color, x, y, txt_string) { text.setPosition(x, y); text.setFont(font); text.setStyle(Text::Bold); text.setCharacterSize(size); text.setFillColor(color); text.setString(txt_string); }