#pragma once

//SDL includes
#include "../SDL2-2.0.5/include/SDL.h"
#include "../SDL2-2.0.5/SDL2_image-2.0.1/include/SDL_image.h"
#include "Vector3D.h"
#include "Tile.h"
#include "common.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::getline;
using std::istringstream;



class Map{
	public:
		Map();
		~Map();

		void DrawMap();

		Tile** GetTiles() const{
			return tiles;
		}

	private:
		Tile **tiles;
};