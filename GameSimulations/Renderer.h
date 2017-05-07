#pragma once

#include "common.h"

#include "Map.h"
#include "Entity.h"

#include <string>
#include <iostream>

//SDL includes
#include "../SDL2-2.0.5/include/SDL.h"
#include "../SDL2-2.0.5/SDL2_image-2.0.1/include/SDL_image.h"

using std::string;
using std::cout;
using std::endl;

class Renderer{
	public:
		Renderer();
		~Renderer();

		bool CheckInputs();
		void RenderScene(float msec);

	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_GLContext context;
		SDL_Surface *screen;
		Map *map;
		Entity *player;
		SDL_Texture *playerTex;

		void DrawMap();
		SDL_Texture* LoadTex(string texfile);
};