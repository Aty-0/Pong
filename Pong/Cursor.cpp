//===================Cursor.cpp========================
// Purpose:			Simple Cursor
//
//=====================================================

#include "Cursor.h"

//Create Cursor
CCursor::CCursor()
{
	logger->Print("Create Cursor", logger->Debug);
	//Cursor Image need for transperent texture

	if (!CursorIMG.loadFromFile("Gamedata/Textures/cursor.png"))
	{
		logger->Print("Can't load image for cursor!", logger->Error);
		game->m_MouseVisible = true;
	}
	else
	{
		//Load from image
		CursorTex.loadFromImage(CursorIMG);
		//Smooth
		CursorTex.setSmooth(true);
		//Set Texture and scale
		CursorSprite.setTexture(CursorTex);
		CursorSprite.setScale(1, 1);
	}
	CursorGlobalBounds = CursorSprite.getGlobalBounds();
}


CCursor::~CCursor()
{
	Visible = false;
}

//Update Position
void CCursor::Update(RenderWindow &window)
{
	if (Visible == true)
	{
		//Get Mouse X
		CursorPos.x = Mouse::getPosition(window).x;
		//Get Mouse Y
		CursorPos.y = Mouse::getPosition(window).y;
		//Set Position for sprite
		CursorSprite.setPosition(CursorPos);
	}
}

//Drawing Cursor
void CCursor::Draw(RenderWindow &window)
{
	if (Visible == true)
		window.draw(CursorSprite);
}

