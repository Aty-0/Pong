//===================SoundLoader.cpp=====================
// Purpose:		Sound Loader / Playing sounds and ambient
//
//=======================================================

#include "SoundLoader.h"
#include "Logger.h"

void CSoundLoader::PlaySoundFromFile(std::string Path, float Volume, float Pitch, bool Loop)
{
	if (!m_buffer.loadFromFile(Path))
		logger->Print("Can't open music file!! Maybe file is not exist | PATH = " + std::string(Path), logger->Error);
	else
	{
		//logger->Print("Sound played " + std::string(Path) + " Volume = " + to_string(Volume) + " Pitch = " + to_string(Pitch) + " Loop = " + to_string(Loop), logger->Debug);
		m_sound.setBuffer(m_buffer);
		m_sound.setLoop(Loop);
		m_sound.setPitch(Pitch);
		//m_sound.setPlayingOffset(m_Offset);
		m_sound.setVolume(Volume);
		m_sound.play();
	}
}

void CSoundLoader::StopAllSounds()
{
	m_sound.stop();
	m_music.stop();
}

void CSoundLoader::PlayAmbFromFile(std::string Path, float Volume, float Pitch)
{
	if (!m_music.openFromFile(Path))
		logger->Print("Can't open music file!! Maybe file is not exist | PATH = " + std::string(Path), logger->Error);
	else
	{
		//logger->Print("Amb played " + std::string(Path) + " Volume = " + to_string(Volume) + " Pitch = " + to_string(Pitch), logger->Debug);
		m_music.setPitch(Pitch);
		m_music.setVolume(Volume);
		m_music.setLoop(true);
		m_music.play();
	}
}