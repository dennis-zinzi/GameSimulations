#include "Entity.h"
#include "Renderer.h"
#include "Utilities.h"


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