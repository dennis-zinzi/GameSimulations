#pragma once
#include "Vector3D.h"

class Entity {
	public:
		Entity(float aggroRange = 1.0f);
		Entity(const Vector3D &v, float aggroRange = 1.0f);
		Entity(float x, float y, float z, float aggroRange = 1.0f);


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

		inline void updateEntitiesInRange(int entitiesInRange){
			this->entitiesInRange = entitiesInRange;
		}

		inline int getEntitiesInRange(){
			return entitiesInRange;
		}

		/* Sigle components getter and setter methods */
		inline void updateXPos(float x){
			pos.setX(x);
		}

		inline float getXPosition(){
			return pos.getX();
		}

		inline void updateYPos(float y){
			pos.setY(y);
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
		

	private:
		Vector3D pos;
		float aggroRange;
		int entitiesInRange;
};