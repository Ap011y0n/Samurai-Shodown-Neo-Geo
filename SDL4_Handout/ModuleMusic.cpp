#include "Globals.h"
#include "Application.h"
#include "ModuleMusic.h"

#include "SDL/include/SDL.h"
#include "SDL_Mixer/Include/SDL_mixer.h"

#pragma comment(lib, "SDL_Mixer/libx86/SDL2_mixer.lib")

ModuleMusic::ModuleMusic() :Module()
{
	for (uint i = 0; i < MAX_MUSIC; ++i)
		musics[i] = nullptr;

	for (uint i = 0; i < MAX_MUSIC; ++i)
		chunks[i] = nullptr;
}

ModuleMusic::~ModuleMusic()
{}

bool ModuleMusic::Init()
{
	LOG("Init Music library");
	bool ret = true;
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Music lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	return ret;

}

bool ModuleMusic::CleanUp()
{
	LOG("Freeing music library");

	for (uint i = 0; i < MAX_MUSIC; ++i)
		if (musics[i] != nullptr)
			Mix_FreeMusic(musics[i]);
	for (uint i = 0; i < MAX_MUSIC; ++i)
		if (chunks[i] != nullptr)
			Mix_FreeChunk(chunks[i]);

	Mix_CloseAudio();
	Mix_Quit();
	return true;
}


Mix_Music* const ModuleMusic::LoadMus(const char* path) {
	int i = 0;
	bool room = false;
	for (i = 0; i < MAX_MUSIC; ++i)
	{
		if (musics[i] == nullptr)
		{
			musics[i] = Mix_LoadMUS(path);
			room = true;
			break;
		}
	}
	if (room == false)
		LOG("Music buffer overflow");
	return musics[i];
}

Mix_Chunk* const ModuleMusic :: LoadChunk(const char* path) {
	int i = 0;
	bool room = false;
	for (i = 0; i < MAX_MUSIC; ++i)
	{
		if (chunks[i] == nullptr)
		{
			chunks[i] = Mix_LoadWAV(path);
			room = true;
			break;
		}
	}
	if (room == false)
		LOG("Song buffer overflow");
	return chunks[i];
}

bool  ModuleMusic::Unload(Mix_Music * music, Mix_Chunk * chunk)
{
	bool ret = false;

	if (music != nullptr)
	{
		for (int i = 0; i < MAX_MUSIC; ++i)
		{
			if (musics[i] == music)
			{
				musics[i] = nullptr;
				ret = true;
				break;
			}
		}
		Mix_FreeMusic(music);
	}
	if (chunk != nullptr)
	{
		for (int i = 0; i < MAX_MUSIC; ++i)
		{
			if (chunks[i] == chunk)
			{
				chunks[i] = nullptr;
				ret = true;
				break;
			}
		}
		Mix_FreeChunk(chunk);
	}

	return ret;
}