#include "Fonts.h"
#include "core/Logger.h"

namespace sbt
{
	Fonts::Fonts()
	{

	}

	Fonts::~Fonts()
	{
		m_fonts.clear();
		m_fonts.shrink_to_fit();
	}

	void Fonts::loadFontFromFile(const char* path, const char* name)
	{
		sf::Font font = { };
		if (!font.loadFromFile(path))
		{
			ERR("Can't load font from path %s", path);
			return;
		}

		m_fonts.push_back(std::make_pair(name, font));
	}

	sf::Font Fonts::getFont(const char* name)
	{
		auto it = std::find_if(m_fonts.begin(), m_fonts.end(),
			[name](std::pair<const char*, sf::Font> el) { return el.first == name; });

		if (it == m_fonts.end())
		{
			ERR("Font with %s name is not exist", name);
			return sf::Font();
		}

		return it->second;
	}
}
