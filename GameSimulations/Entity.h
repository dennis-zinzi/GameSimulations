#pragma once

#include "common.h"
#include "Vector2D.h"
#include "Tile.h"
#include "Map.h"
//#include "PhysicsManager.h"

#include <vector>

using std::vector;


enum FORCE{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class Entity {
	public:
		Entity(Map *map, float mass = 1.0f);
		Entity(const Vector2D &v, Map *map, float mass = 1.0f);
		Entity(float x, float y, Map *map, float mass = 1.0f);

		
		void updatePos(const Vector2D &pos);

		inline Vector2D getPosition(){
			return pos;
		}

		inline Vector2D getVelocity(){
			return velocity;
		}

		void setVelocity(Vector2D vel);

		
		/* Sigle components getter and setter methods */
		inline void updateXPos(float x){
			//Only move if within window bounds
			if(pos.getX() + x > 0 && pos.getX() + x < WINDOW_WIDTH - (TILE_LENGTH / 2)){
				pos.setX(pos.getX() + x);
			}
		}

		inline float getXPosition(){
			return pos.getX();
		}

		inline void updateYPos(float y){
			//Only move if within window bounds
			if(pos.getY() + y > 0 && pos.getY() + y < WINDOW_HEIGHT - (TILE_LENGTH / 2)){
				pos.setY(pos.getY() + y);
			}
		}

		inline float getYPosition(){
			return pos.getY();
		}



		inline float getMass() const{
			return mass;
		}


		/**
		 * Updates Entity's current tile
		 */
		inline void updateTile(){
			//Update which Tile entity is in based on pos	
			currTile = map->GetTiles()[(int)(pos.getY() + 7.5f) / TILE_LENGTH][(int)(pos.getX() + 10) / TILE_LENGTH];

			//cout << "Tile multi: " << currTile.GetTileMultiplier() << endl;
		}

		inline bool getWin() const{
			return win;
		}

		inline Tile getCurrentTile() const{
			return currTile;
		}


		inline void setPath(vector<Vector2D> path){
			this->path = path;
		}

		inline vector<Vector2D> getPath() const{
			return path;
		}

		inline int getCurrentIndex() const{
			return currentIndex;
		}

		inline void setCurrentIndex(int index){
			currentIndex = index;
		}

	private:
		Vector2D pos;
		Vector2D velocity;
		Tile currTile;
		Map *map;
		float mass;
		bool win;

		vector<Vector2D> path;
		int currentIndex;
};