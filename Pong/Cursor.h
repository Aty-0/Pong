//===================Cursor.h==========================
// Purpose:			Simple Cursor
//
//=====================================================

#pragma once
#include "Game.h"
class CCursor
{
public:
	//Cursor Image,Texture,Sprite
	Image CursorIMG;
	Texture CursorTex;
	Sprite CursorSprite;
	//X and Y Cursor
	Vector2f CursorPos;
	FloatRect CursorGlobalBounds;
	//Visible of cursor
	bool Visible = true;
	//Creating Cursor
	CCursor();
	//Dispose Cursor
	virtual ~CCursor();
	//Update
	virtual void Update(RenderWindow &window);
	//Render
	virtual void Draw(RenderWindow &window);
};

