#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMenu.h"
#include "SDL/include/SDL.h"
#include "ModuleVictoryHaohmaru.h"


ModuleVictoryHaohmaru::ModuleVictoryHaohmaru()
{
	win.x = 1407;
	win.y = 204;
	win.w = 309;
	win.h = 225;
}

ModuleVictoryHaohmaru::~ModuleVictoryHaohmaru()
{}

// Load assets
bool ModuleVictoryHaohmaru::Start()
{
	LOG("Loading win assets");
	bool ret = true;

	musload = App->music->LoadMus("Assets/Sound/Conclusion (Winning Demo).ogg");
	graphics = App->textures->Load("Assets/Image/menu_victory.png");
	App->music->PlayMus(musload);

	return ret;
}

bool ModuleVictoryHaohmaru::CleanUp()
{
	LOG("Unloading Menu scene");
	App->music->UnloadMus(musload);
	App->textures->Unload(graphics);
	
	return true;
}

// Update: draw background
update_status ModuleVictoryHaohmaru::Update()
{

	// Draw everything --------------------------------------

	App->render->Blit(graphics, 38, 0, &win);
	


	//background

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(App->winhaoh, App->menu, 2);
	}

	return UPDATE_CONTINUE;
}