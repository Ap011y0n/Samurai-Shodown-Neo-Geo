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
	Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 1024);

	return ret;

}

bool ModuleMusic::CleanUp()
{
	LOG("Freeing music library");
	
	uint i = 0;
	for (i = 0; i < MAX_MUSIC; ++i)
		if (musics[i] != nullptr){
			Mix_FreeMusic(musics[i]);

	}
	for (i = 0; i < MAX_MUSIC; ++i)
		if (chunks[i] != nullptr){
			Mix_FreeChunk(chunks[i]);
			
	}
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
			if (!musics[i]) {
				LOG("Cannot load music");
			}
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
			if (!chunks[i]) {
				LOG("Cannot load chunk");
			}
			
			room = true;
			break;
		}
	}
	if (room == false){
		LOG("FX buffer overflow");}

	return chunks[i];
}
void  ModuleMusic::PlayChunk(Mix_Chunk * chunk) {

	if (chunk != nullptr) {
		Mix_FadeInChannel(-1, chunk, 0, 500);
		chunk = nullptr;
	}
}

void  ModuleMusic::PlayMus(Mix_Music * music) {

	if (music != nullptr) {
		Mix_FadeInMusic(music, -1, 1000);
		music = nullptr;
	}

}

bool  ModuleMusic::UnloadChunk(Mix_Chunk * chunk)
{
	bool ret = false;
	int i = 0;

	if (chunk != nullptr)
	{
		for (i = 0; i < MAX_MUSIC; ++i)
		{
			if (chunks[i] == chunk)
			{
				chunks[i] = nullptr;
				ret = true;
				break;
			}
		}
		Mix_FadeOutChannel(-1, 1000);
	}
	return ret;
}

	bool  ModuleMusic::UnloadMus(Mix_Music * music)
	{
		bool ret = false;
		int i = 0;

		if (music != nullptr)
		{
			for (i = 0; i < MAX_MUSIC; ++i)
			{
				if (musics[i] == music)
				{
					musics[i] = nullptr;
					ret = true;
					break;
				}
			}
			Mix_FadeOutMusic(1000);
		}

	return ret;
}