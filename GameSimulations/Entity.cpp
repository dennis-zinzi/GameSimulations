#include "Entity.h"

Entity::Entity(float aggroRange){
	pos = Vector3D(0.0f, 0.0f, 0.0f);
	this->aggroRange = aggroRange;
	entitiesInRange = 0;
}

Entity::Entity(const Vector3D &v, float aggroRange){
	pos = v;
	this->aggroRange = aggroRange;
	entitiesInRange = 0;
}

Entity::Entity(float x, float y, float z, float aggroRange){
	pos = Vector3D(x, y, z);
	this->aggroRange = aggroRange;
	entitiesInRange = 0;
}


void Entity::UpdateEntity(vector<Entity*> entites){
	for(auto e : entites){
		if(e->getPosition().getX()){

		}
	}
}