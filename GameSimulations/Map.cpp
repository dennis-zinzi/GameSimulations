#include "Map.h"

Map::Map(){
	ifstream map(FILES_PATH"map_details.txt");

	if(!map.good()){
		cout << "ERROR: map file not found" << endl;
		return;
	}

	//Create 2D array of Tiles
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
			t.SetCenter(Vector3D(TILE_LENGTH * column, TILE_LENGTH * row, 0));

			switch(c){
				case 'B':
					t.SetType(TileType::BASE);
					break;
				case 'O':
					t.SetType(TileType::OPEN);
					break;
				case 'C':
					t.SetType(TileType::COVERED);
					break;
				case 'P':
					t.SetType(TileType::BRIDGE);
					break;
				case 'F':
					t.SetType(TileType::FOREST);
					break;
				case 'R':
					t.SetType(TileType::RIVER);
					break;
				case 'G':
					t.SetType(TileType::GATE);
					break;
				case 'W':
					t.SetType(TileType::WALL);
					break;
				case 'V':
					t.SetType(TileType::CASTLE);
			}

			tiles[row][column] = t;
			column++;
		}

		row++;
	}
}


vector<PathNode*> Map::GetMapAsPathNodes() const{
	vector<PathNode*> nodes;
	int n = 0;

	for(int i = 0; i < TILES_IN_ROW; i++){
		for(int j = 0; j < TILES_IN_ROW; j++){
			Tile t = tiles[i][j];

			PathNode *node = new PathNode(n, t.GetCenter(), t.GetType());
			if(t.GetType() == TileType::WALL){
				node->bIsPassable = false;
			}

			nodes.push_back(node);
			n++;
		}
	}

	return nodes;
}