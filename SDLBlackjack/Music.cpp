#include <algorithm>
#include <assert.h>
#include "Music.h"
#include <iostream>

std::string Music::s_rootFolder = "Assets/Music/";
std::unique_ptr<Musics> Music::s_musics = std::make_unique<Musics>();

//======================================================================================================
bool Music::Initialize(int frequency, int chunkSize)
{
	if (Mix_OpenAudio(frequency, AUDIO_S16SYS, 2, chunkSize) == -1)
	{
		std::cout << "Error initializing the audio sub-system." << std::endl;
		return false;
	}

	return true;
}
//======================================================================================================
bool Music::Load(const std::string& filename, const std::string& tag)
{
	assert(s_musics->find(tag) == s_musics->end());

	Mix_Music* music = Mix_LoadMUS((s_rootFolder + filename).c_str());

	if (!music)
	{
		std::cout << "Error loading music file \"" + (s_rootFolder + filename) + "\"\n\n"
						"Possible causes could be a corrupt or missing file. Another reason could be "
						"that the filename and/or path are incorrectly spelt." << std::endl;
		return false;
	}

	s_musics->insert(std::pair<std::string, Mix_Music*>(tag, music));
	return true;
}
//======================================================================================================
void Music::Unload(const std::string& tag)
{
	if (!tag.empty())
	{
		auto it = s_musics->find(tag);
		assert(it != s_musics->end());
		Mix_FreeMusic(it->second);
		s_musics->erase(it);
	}

	else
	{
		for (const auto& music : *s_musics)
		{
			Mix_FreeMusic(music.second);
		}

		s_musics->clear();
	}
}
//======================================================================================================
void Music::Shutdown()
{
	Mix_CloseAudio();
}
//======================================================================================================
void Music::SetVolume(float volume)
{
	volume = std::clamp(volume, 0.0f, 1.0f);
	Mix_VolumeMusic(static_cast<int>(volume * 128.0f));
}
//======================================================================================================
bool Music::SetMusic(const std::string& tag)
{
	auto it = s_musics->find(tag);
	assert(it != s_musics->end());
	m_music = (*it).second;
	return true;
}
//======================================================================================================
bool Music::Play(Loop loop)
{
	if (!Mix_PlayingMusic())
	{
		if (Mix_PlayMusic(m_music, static_cast<int>(loop)) == -1)
		{
			std::cout << "Music could not be played." << std::endl;
			return false;
		}
	}

	return true;
}
//======================================================================================================
void Music::Pause()
{
	if (!Mix_PausedMusic())
	{
		Mix_PauseMusic();
	}
}
//======================================================================================================
void Music::Resume()
{
	if (Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
}
//======================================================================================================
void Music::Stop()
{
	if (Mix_PlayingMusic())
	{
		Mix_HaltMusic();
	}
}