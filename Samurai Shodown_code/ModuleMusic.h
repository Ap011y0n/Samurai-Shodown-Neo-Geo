#ifndef __ModuleMusic_H__
#define __ModuleMusic_H__

#include "Module.h"
#include "Globals.h"
#include "SDL_Mixer/Include/SDL_mixer.h"

#define MAX_MUSIC 10
#define MAX_EFFECTS 50



class ModuleMusic : public Module
{
public:
	ModuleMusic();
	~ModuleMusic();
	bool Init();
	bool CleanUp();

	Mix_Music* const LoadMus(const char* path);
	Mix_Chunk* const LoadChunk(const char* path);
	void PlayChunk(Mix_Chunk * chunk);
	void PlayMus(Mix_Music * music);
	bool UnloadChunk(Mix_Chunk * chunk);
	bool UnloadMus(Mix_Music * music);
	
public:
	Mix_Music *musics[MAX_MUSIC];
	Mix_Chunk *chunks[MAX_EFFECTS];
};

#endif //