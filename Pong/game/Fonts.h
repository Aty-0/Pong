#pragma once
#include "core/common.h"

namespace sbt
{
	class Fonts : public sbt::Singleton<Fonts>
	{
	public:
		Fonts();
		~Fonts();
		
		void loadFontFromFile(const char* path, const char* name);
		sf::Font getFont(const char* name);

	private:
		std::vector<std::pair<const char*, sf::Font>> m_fonts;
	};
}