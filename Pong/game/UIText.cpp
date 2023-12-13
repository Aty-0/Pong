#include "UIText.h"
#include "Fonts.h"

namespace sbt
{
	UIText::UIText()
	{
		m_text = createDrawableWithType<sf::Text>();
		
		setFont("default");
		setFontSize(16);

		// todo: in game object
		m_text->setFillColor(sf::Color::White);

		m_text->setString("string");
	}
	
	UIText::~UIText()
	{

	}
	
	void UIText::setText(std::string text)
	{
		m_text->setString(text);
	}

	void UIText::setFontSize(std::uint32_t size)
	{
		m_text->setCharacterSize(size);
	}

	void UIText::setFont(const char* fontName)
	{
		m_font = sbt::Fonts::getInstance()->getFont(fontName);
		m_text->setFont(m_font);
	}

}