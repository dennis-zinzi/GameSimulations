#include "Entity.h"
#include "Renderer.h"
#include "Utilities.h"
#include "Game.h"


int main(int argc, char **argv){
	bool running = true;

	Map *map = new Map();

	Renderer *renderer = new Renderer(map);
	PhysicsManager *physics = new PhysicsManager();

	Game game(renderer, physics, map);

	float msec = SDL_GetTicks();

	while(running){
		msec = SDL_GetTicks() - msec;
		running = game.CheckInputs();//renderer->CheckInputs();
		game.UpdateEntities();
		game.RenderScene(msec);
	}

	delete renderer;

	return 0;
}