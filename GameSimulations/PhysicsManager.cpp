#include "PhysicsManager.h"


PhysicsManager::PhysicsManager(){
	timeStep = (1.0f / PHYSICS_RATE);
}


void PhysicsManager::UpdatePhysics(float msec){

}


void PhysicsManager::UpdateVelocity(Entity *e, bool *forces){
	Vector3D acceleration;
	if(forces[UP]){
		acceleration.setY(acceleration.getY() - ACCELERATION);
	}
	else if(forces[DOWN]){
		acceleration.setY(acceleration.getY() + ACCELERATION);
	}
	else{
		e->setVelocity(Vector3D(e->getVelocity().getX(), 0.0f, 0.0f));
	}

	if(forces[LEFT]){
		acceleration.setX(acceleration.getX() - ACCELERATION);
	}
	else if(forces[RIGHT]){
		acceleration.setX(acceleration.getX() + ACCELERATION);
	}
	else{
		e->setVelocity(Vector3D(0.0f, e->getVelocity().getY(), 0.0f));
	}

	Vector3D vel = e->getVelocity() + acceleration*timeStep;
	//cout << "New v: " << vel.magnitude() << endl;
	e->setVelocity(vel);
}


void PhysicsManager::UpdateEntityPos(Entity *e){
	Vector3D pos = e->getPosition() + e->getVelocity()*timeStep;
	e->updatePos(pos);
	e->updateTile();
}



bool PhysicsManager::IsEntityCollidingWithEntity(Entity *colliding, Entity *e){

	//Get current entity's
	float xMin = colliding->getXPosition(),
		yMin = colliding->getYPosition();

	//Get other's max and min x coords for e
	float sMinX = e->getXPosition(),
		sMaxX = e->getXPosition() + ENTITY_WIDTH;

	//Get max and min y coords for e
	float sMinY = e->getYPosition(),
		sMaxY = e->getYPosition() + ENTITY_HEIGHT;

	float xCenter = xMin + (ENTITY_WIDTH / 2.0f),
		yCenter = yMin + (ENTITY_HEIGHT / 2.0f);

	//If Center of current entity is within e' bounds, then definitely collided
	if(xCenter >= sMinX && xCenter <= sMaxX
		&& yCenter >= sMinY && yCenter <= sMaxY){
		return true;
	}

	//Get max x and y coords for current entity
	float xMax = xMin + ENTITY_WIDTH,
		yMax = yMin + ENTITY_HEIGHT;

	//Check if Entity overlaps with e
	if((xMax >= sMinX) && (sMaxX >= xMin) && (yMax >= sMinY) && (sMaxY >= yMin)){
		//If current entity is anywhere between the bounds of e then must overlap
		return true;
	}

	//Any other scenario entities don't overlap
	return false;
}


void PhysicsManager::handleEntityCollision(Entity *eHitting, Entity *eHit, bool *forces){
	UpdateVelocity(eHitting, forces);
	UpdateVelocity(eHit, forces);

	UpdateEntityPos(eHitting);
	UpdateEntityPos(eHit);
}