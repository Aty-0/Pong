#include "SoundLoader.h"
#include "core/Logger.h"

namespace sbt
{
	SoundLoader::SoundLoader() : m_masterVolume(0.3f)
	{

	}

	SoundLoader::~SoundLoader()
	{

	}

	void SoundLoader::playSound(const char* name, float Volume, float Pitch, bool Loop)
	{		
		// Don't play when other sound is played
		//if (m_sound.getStatus() == sf::Sound::Playing)
		//	return;

		auto it = std::find_if(m_sounds.begin(), m_sounds.end(),
			[name](std::pair<const char*, sf::SoundBuffer> el) { return el.first == name; });

		if (it == m_sounds.end())
		{
			ERR("Sound with %s name is not exist", name);
			return;
		}

		m_sound.setBuffer(it->second);
		m_sound.setLoop(Loop);
		m_sound.setPitch(Pitch);
		m_sound.setVolume(m_masterVolume * Volume);
		m_sound.play();
	}

	void SoundLoader::loadSound(const char* name, const char* path)
	{
		sf::SoundBuffer buffer;
		if (!buffer.loadFromFile(path))
		{
			ERR("playSoundFromFile Can't open sound file! %s", path);
			return;
		}

		m_sounds.push_back(std::make_pair(name, buffer));
	}

	void SoundLoader::stopAllSounds()
	{
		m_sound.stop();
		m_track.stop();
	}

	void SoundLoader::playTrack(const char* Path, float Volume, float Pitch)
	{
		if (!m_track.openFromFile(Path))
		{
			ERR("playAmbFromFile Can't open sound file! %s", Path);
		}
		else
		{
			m_track.setPitch(Pitch);
			m_track.setVolume(m_masterVolume * Volume);
			m_track.setLoop(true);
			m_track.play();
		}
	}

	void SoundLoader::setMasterVolume(float volume)
	{
		m_masterVolume = volume;
	}

	float SoundLoader::getMasterVolume() const
	{
		return m_masterVolume;
	}
}