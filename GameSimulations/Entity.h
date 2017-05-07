#pragma once
#include "Vector3D.h"
#include "common.h"

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
		Entity(float aggroRange = 1.0f);
		Entity(const Vector3D &v, float aggroRange = 1.0f);
		Entity(float x, float y, float z, float aggroRange = 1.0f);

		void UpdateEntity(vector<Entity*> entites);


		inline void updateAggroRange(float aggroRange){
			this->aggroRange = aggroRange;
		}

		inline float getAggroRange(){
			return aggroRange;
		}

		inline void updatePos(const Vector3D &pos){
			this->pos = pos;
		}

		inline Vector3D getPosition(){
			return pos;
		}

		inline Vector3D getVelocity(){
			return velocity;
		}

		inline void setVelocity(Vector3D vel){
			velocity = vel;
		}

		inline void updateEntitiesInRange(int entitiesInRange){
			this->entitiesInRange = entitiesInRange;
		}

		inline int getEntitiesInRange(){
			return entitiesInRange;
		}

		/* Sigle components getter and setter methods */
		inline void updateXPos(float x){
			//pos.setX(x);
			if(pos.getX() + x > 0 && pos.getX() + x < WINDOW_WIDTH - (TILE_LENGTH / 2)){
				pos.setX(pos.getX() + x);
			}
		}

		inline float getXPosition(){
			return pos.getX();
		}

		inline void updateYPos(float y){
			if(pos.getY() + y > 0 && pos.getY() + y < WINDOW_HEIGHT - (TILE_LENGTH / 2)){
				pos.setY(pos.getY() + y);
			}
		}

		inline float getYPosition(){
			return pos.getY();
		}

		inline void updateZPos(float z){
			pos.setZ(z);
		}

		inline float getZPosition(){
			return pos.getZ();
		}

		inline Vector3D getDirVector() const{
			return pos.makeUnitVector3D();
		}

		inline float getEntityDir() const{
			Vector3D unit = pos.makeUnitVector3D();
			return atan2(unit.getY(), unit.getX()) * (180 / PI_VAL);
		}
		

	private:
		Vector3D pos;
		Vector3D velocity;
		float aggroRange;
		int entitiesInRange;
};