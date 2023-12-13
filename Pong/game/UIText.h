#pragma once
#include "game/GameObject.h"

namespace sbt
{
	class UIText : public GameObject
	{
	public:
		UIText();
		~UIText();

		void setText(std::string text);
		void setFontSize(std::uint32_t size);
		void setFont(const char* fontName);

	private:
		sf::Text* m_text;
		sf::Font  m_font;
	};
}