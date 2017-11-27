#pragma once

//SDL include
#include "../SDL2-2.0.5/include/SDL.h"

#include "Vector3D.h"
#include "Tile.h"
#include "PathNode.h"

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

		inline Tile** GetTiles() const{
			return tiles;
		}

		vector<PathNode*> GetMapAsPathNodes() const;

	private:
		Tile **tiles;
};