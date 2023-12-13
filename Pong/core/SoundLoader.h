#pragma once
#include "common.h"
#include <SFML\Audio.hpp>

namespace sbt
{
	class SoundLoader : public sbt::Singleton<SoundLoader>
	{
	public:
		SoundLoader();
		~SoundLoader();

		void stopAllSounds();

		void loadSound(const char* name, const char* path);
		void playSound(const char* name, float Volume, float Pitch, bool Loop);
		
		void playTrack(const char* path, float Volume, float Pitch);

	private:
		std::vector<std::pair<const char*, sf::SoundBuffer>> m_sounds;
		sf::Music m_track;
		sf::Sound m_sound;
	};
}
