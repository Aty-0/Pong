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
		sound.setBuffer(m_buffer);
		sound.setLoop(Loop);
		sound.setPitch(Pitch);
		//sound.setPlayingOffset(m_Offset);
		sound.setVolume(Volume);
		sound.play();
	}
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