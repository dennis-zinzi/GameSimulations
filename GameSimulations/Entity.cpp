#include "Entity.h"

Entity::Entity(float aggroRange){
	pos = Vector3D(0.0f, 0.0f, 0.0f);
	this->aggroRange = aggroRange;
	entitiesInRange = 0;
}

Entity::Entity(const Vector3D &v, Map *map, float aggroRange){
	pos = v;

	cout << (map == nullptr ? "y" : "n") << endl;
	currTile = map->GetTiles()[(int)pos.getX() / TILE_LENGTH][(int)pos.getY() / TILE_LENGTH];

	this->map = map;
	this->aggroRange = aggroRange;
	entitiesInRange = 0;
}

Entity::Entity(float x, float y, float z, Map *map, float aggroRange){
	pos = Vector3D(x, y, z);
	this->aggroRange = aggroRange;
	entitiesInRange = 0;

	cout << (map == nullptr ? "y" : "n") << endl;
	currTile = map->GetTiles()[(int)pos.getX() / TILE_LENGTH][(int)pos.getY() / TILE_LENGTH];

	this->map = map;
}


void Entity::updatePos(const Vector3D &pos){
	if(pos.getX() > 0 && pos.getX() < WINDOW_WIDTH - (TILE_LENGTH / 2)){
		this->pos.setX(pos.getX());
	}
	if(pos.getY() > 0 && pos.getY() < WINDOW_HEIGHT - (TILE_LENGTH / 2)){
		this->pos.setY(pos.getY());
	}
	//this->pos = pos;
	//updateTile();


	//cout << (int)pos.getX() / TILE_LENGTH << endl;
}


void Entity::setVelocity(Vector3D vel){
	//Check if passed max velocity
	if(vel.magnitude() < MAX_VEL * currTile.GetTileMultiplier()){
		velocity = vel;
	}
	//If over max velocity get direction, and set velocity to max
	else{
		Vector3D v = vel.makeUnitVector3D();
		v *= MAX_VEL * currTile.GetTileMultiplier();

		velocity = v;
	}
}


void Entity::UpdateEntity(vector<Entity*> entites){
	for(auto e : entites){
		if(e->getPosition().getX()){

		}
	}
}