#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleMusic.h"


struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
private:
	int jump;
	bool floor = true;
	bool attAnim= false;
	bool kickAnim = false;
	bool cycloneAnim = false;
	int initialPos;
	float jumpSpeed = 6;
	int animstart=0;
	bool wall = false;
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Mix_Chunk* senpuu;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation jumpup;
	Animation punch;
	Animation kick;
	Animation cyclone;
	iPoint position;

	Collider *colliderPlayer;

};

#endif