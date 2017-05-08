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


void Entity::updatePos(const Vector3D &pos){
	if(pos.getX() > 0 && pos.getX() < WINDOW_WIDTH - (TILE_LENGTH / 2)){
		this->pos.setX(pos.getX());
	}
	if(pos.getY() > 0 && pos.getY() < WINDOW_HEIGHT - (TILE_LENGTH / 2)){
		this->pos.setY(pos.getY());
	}
	//this->pos = pos;
}


void Entity::setVelocity(Vector3D vel){
	//std::cout << velocity.magnitude() << std::endl;
	if(vel.magnitude() < MAX_VEL){
		velocity = vel;
	}
	else{
		Vector3D v = vel.makeUnitVector3D();
		v *= MAX_VEL;

		velocity = v;
	}
}


void Entity::UpdateEntity(vector<Entity*> entites){
	for(auto e : entites){
		if(e->getPosition().getX()){

		}
	}
}