#pragma once

#include "common.h"
#include "Utilities.h"

#include "Map.h"
#include "Entity.h"
#include "PhysicsManager.h"
#include "BoidFlock.h"
#include "AStar.h"

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
		Renderer(Map *map);
		~Renderer();

		void RenderScene(float msec, vector<Entity*> entities, Entity *player);

		void RenderEntity(Entity *e);

		SDL_Texture* LoadTex(string texfile);

	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_GLContext context;
		SDL_Surface *screen;
		Map *map;

		vector<Texture> textures;

		//Draws map of tiles
		void DrawMap();
		
};