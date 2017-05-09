#include "Entity.h"

Entity::Entity(Map *map, float mass){
	pos = Vector2D(0.0f, 0.0f);
	this->mass = mass;
	
	win = false;
	this->map = map;
	currentIndex = 0;
}

Entity::Entity(const Vector2D &v, Map *map, float mass){
	pos = v;
	
	//Set tile
	currTile = map->GetTiles()[(int)pos.getX() / TILE_LENGTH][(int)pos.getY() / TILE_LENGTH];

	this->mass = mass;
	this->map = map;
	
	win = false;
	currentIndex = 0;
}

Entity::Entity(float x, float y, Map *map, float mass){
	pos = Vector2D(x, y);
	
	currTile = map->GetTiles()[(int)pos.getX() / TILE_LENGTH][(int)pos.getY() / TILE_LENGTH];

	this->map = map;
	this->mass = mass;
	win = false;
	currentIndex = 0;
}


void Entity::updatePos(const Vector2D &pos){
	if(pos.getX() > 0 && pos.getX() < WINDOW_WIDTH - (TILE_LENGTH / 2)){
		this->pos.setX(pos.getX());
	}
	if(pos.getY() > 0 && pos.getY() < WINDOW_HEIGHT - (TILE_LENGTH / 2)){
		this->pos.setY(pos.getY());
	}
}


void Entity::setVelocity(Vector2D vel){

	if(currTile.GetType() == TileType::CASTLE){
		win = true;
	}

	//Check if over max velocity
	if(vel.magnitude() < MAX_VEL * currTile.GetTileMultiplier()){
		velocity = vel;
	}
	//If over max velocity get direction, and set velocity to max
	else{
		Vector2D v = vel.makeUnitVector2D();
		v *= MAX_VEL * currTile.GetTileMultiplier();

		velocity = v;
	}
}
