//===================SoundLoader.h=======================
// Purpose:		Sound Loader / Playing sounds and ambient
//
//=======================================================

#pragma once
#include <SFML\Audio.hpp>
using namespace sf;

class CSoundLoader
{
public:
	SoundBuffer m_buffer;
	Sound sound;
	Music m_music;
	//Time m_Offset;
	virtual void PlaySoundFromFile(std::string Path, float Volume, float Pitch, bool Loop);
	virtual void PlayAmbFromFile(std::string Path, float Volume, float Pitch);
};

extern CSoundLoader *soundloader;
