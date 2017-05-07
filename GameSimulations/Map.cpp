#include "Map.h"

Map::Map(){
	ifstream map(FILES_PATH"map_details.txt");

	if(!map.good()){
		cout << "ERROR: map file not found" << endl;
		return;
	}

	tiles = new Tile*[20];
	for(int i = 0; i < 20; ++i){
		tiles[i] = new Tile[20];
	}

	int row = 0;
	for(string line; getline(map, line);){
		//If line starts with # then it's a comment, so ignore it
		if(line.at(0) == '#'){
			continue;
		}

		int column = 0;
		for(char &c : line){
			Tile t;
			t.center = Vector3D(40 * column, 40 * row, 0);

			switch(c){
				case 'B':
					t.type = TileType::BASE;
					break;
				case 'O':
					t.type = TileType::OPEN;
					break;
				case 'C':
					t.type = TileType::COVERED;
					break;
				case 'P':
					t.type = TileType::BRIDGE;
					break;
				case 'F':
					t.type = TileType::FOREST;
					break;
				case 'R':
					t.type = TileType::RIVER;
					break;
				case 'G':
					t.type = TileType::GATE;
					break;
				case 'W':
					t.type = TileType::WALL;
					break;
				case 'V':
					t.type = TileType::CASTLE;
			}

			tiles[row][column] = t;
			column++;
		}

		row++;
	}
}




/*
BASE,
OPEN,
COVERED,
BRIDGE,
FOREST,
RIVER,
GATE,
WALL
*/