/**
* Representation of single tile in Map
*/
#pragma once

#include "Vector2D.h"

enum TileType{
	BASE,
	OPEN,
	COVERED,
	BRIDGE,
	FOREST,
	RIVER,
	GATE,
	WALL,
	CASTLE
};

class Tile{
	public:
		Tile(){
		}

		Tile(Vector2D center, TileType type){
			this->center = center;
			this->type = type;
		}

		inline Vector2D GetCenter() const{
			return center;
		}

		inline TileType GetType() const{
			return type;
		}

		inline void SetCenter(Vector2D center){
			this->center = center;
		}

		inline void SetType(TileType type){
			this->type = type;
		}

		//Get tile velocity vactor
		inline float GetTileMultiplier() const{
			switch(type){
				case BASE:
				case OPEN:
				case COVERED:
				case BRIDGE:
				case CASTLE:
					return 1.0f;
				case FOREST:
					return 0.5f;
				case RIVER:
					return 0.35f;
				case GATE:
					return 0.15f;
				//Used for impulse
				case WALL:
					return 0.5f;
				default:
					return 1.0f;
			}
		}

	private:
		Vector2D center;
		TileType type;
};