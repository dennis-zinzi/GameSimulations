#pragma once

#include "Vector3D.h"

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

		Tile(Vector3D center, TileType type){
			this->center = center;
			this->type = type;
		}

		inline Vector3D GetCenter() const{
			return center;
		}

		inline TileType GetType() const{
			return type;
		}

		inline void SetCenter(Vector3D center){
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
					return 0.15;
				//might change later
				case WALL:
					return 0.0f;
			}
		}

	private:
		Vector3D center;
		TileType type;
};