#pragma once

#include "common.h"

#include "Map.h"

//SDL includes
#include "../SDL2-2.0.5/include/SDL.h"
#include "../SDL2-2.0.5/SDL2_image-2.0.1/include/SDL_image.h"

class Renderer{
	public:
		Renderer();
		~Renderer();

		bool CheckInputs();
		void RenderScene(float msec);

	private:
		SDL_Window *screen;
		SDL_Renderer *renderer;
		SDL_GLContext context;
		Map *map;

		void DrawMap();
};