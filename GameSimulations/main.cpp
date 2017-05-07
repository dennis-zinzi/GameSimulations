#include "Entity.h"
#include "Renderer.h"

#define NUMOFENTITIES 5

Entity* createEntities(){
	Entity entities[NUMOFENTITIES];

	for(int i = 0; i < NUMOFENTITIES; i++){
		entities[i] = Entity();
	}

	return entities;
}

int main(int argc, char **argv){
	bool running = true;

	Renderer *renderer = new Renderer();

	float msec = SDL_GetTicks();

	while(running){
		running = renderer->CheckInputs();

		renderer->RenderScene(msec);
	}

	delete renderer;

	return 0;
}