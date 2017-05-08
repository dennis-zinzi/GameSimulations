#pragma once

#include "common.h"
#include "Utilities.h"

#include "Map.h"
#include "Entity.h"
#include "PhysicsManager.h"

#include <string>
#include <iostream>

//SDL includes
#include "../SDL2-2.0.5/include/SDL.h"
#include "../SDL2-2.0.5/SDL2_image-2.0.1/include/SDL_image.h"

using std::string;
using std::cout;
using std::endl;

//Represents texture (used to avoid loading textures multiple times)
struct Texture{
	string name;
	SDL_Texture *tex;
};


class Renderer{
	public:
		Renderer();
		~Renderer();

		bool CheckInputs();
		void RenderScene(float msec);
		void CreateEntities();

	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_GLContext context;
		SDL_Surface *screen;
		Map *map;
		Entity *player;
		vector<Entity*> ais;

		vector<Texture> textures;

		SDL_Texture *playerTex;
		SDL_Texture *aiTex;
		PhysicsManager *p;

		void DrawMap();
		SDL_Texture* LoadTex(string texfile);
};