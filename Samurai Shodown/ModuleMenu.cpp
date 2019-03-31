#include "Globals.h"
#include "Application.h"
#include "ModuleSceneNakoruru.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleMusic.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleMenu.h"
#include "SDL/include/SDL.h"
#include "ModuleSceneHaohmaru.h"


ModuleMenu::ModuleMenu()
{
	menu.x = 0;
	menu.y = 444;
	menu.w = 303;
	menu.h = 223;

	title.PushBack({ 0, 0, 303, 117 }, 0.005, 0, 0);
	title.PushBack({ 349, 0, 303, 117 }, 0.2, 0, 0);
	title.PushBack({ 698, 0, 303, 117 }, 0.2, 0, 0);
	title.PushBack({ 1046, 0, 303, 117 }, 0.2, 0, 0);
	title.PushBack({ 1395, 0, 303, 117 }, 0.2, 0, 0);
	title.PushBack({ 1744, 0, 303, 117 }, 0.2, 0, 0);
	title.PushBack({ 0, 148, 303, 117 }, 0.2, 0, 0);
	title.PushBack({ 349, 148, 303, 117 }, 0.2, 0, 0);
	title.PushBack({ 698, 148, 303, 117 }, 0.2, 0, 0);
	title.PushBack({ 1046, 148, 303, 117 }, 0.2, 0, 0);
	title.PushBack({ 1395, 148, 303, 117 }, 0.2, 0, 0);
	title.PushBack({ 1743, 148, 303, 117 }, 0.2, 0, 0);
	title.PushBack({ 0, 296, 303, 117 }, 0.2, 0, 0);
	title.PushBack({ 349, 296, 303, 117 }, 0.2, 0, 0);
	title.PushBack({ 698, 296, 303, 117 }, 0.2, 0, 0);
	title.PushBack({ 1046, 296, 303, 117 }, 0.2, 0, 0);

	start.PushBack({ 1395, 296, 120, 14 }, 0.04f,0,0);
	start.PushBack({ 1395, 340, 120, 14 }, 0.025f, 0, 0);
}

ModuleMenu::~ModuleMenu()
{}

// Load assets
bool ModuleMenu::Start()
{
	LOG("Loading menu assets");
	bool ret = true;

	chunkload = App->music->LoadChunk("Assets/Sound/Static and Dynamic (short).ogg");
	graphics = App->textures->Load("Assets/Image/Menu Spritesheet.png");
	App->music->Play(nullptr, chunkload);

	return ret;
}

bool ModuleMenu::CleanUp()
{
	LOG("Unloading Menu scene");
	App->music->Unload(chunkload);
	App->textures->Unload(graphics);
	
	return true;
}

// Update: draw background
update_status ModuleMenu::Update()
{

	App->render->Blit(graphics, 38, 0, &menu);
	App->render->Blit(graphics, 38, 52, &(title.GetCurrentFrame()), 1);
	App->render->Blit(graphics, 124, 172, &(start.GetCurrentFrame()), 1);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		App->fade->FadeToBlack(App->menu, App->scene_haohmaru, 1);
	}

	return UPDATE_CONTINUE;
}