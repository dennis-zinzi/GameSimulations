#include "PhysicsManager.h"


PhysicsManager::PhysicsManager(){
	timeStep = (1.0f / PHYSICS_RATE);
}


void PhysicsManager::UpdatePhysics(float msec){

}


void PhysicsManager::UpdateVelocity(Entity *e, bool *forces){
	Vector2D acceleration;
	if(forces[UP]){
		acceleration.setY(acceleration.getY() - ACCELERATION);
	}
	else if(forces[DOWN]){
		acceleration.setY(acceleration.getY() + ACCELERATION);
	}
	else{
		e->setVelocity(Vector2D(e->getVelocity().getX(), 0.0f));
	}

	if(forces[LEFT]){
		acceleration.setX(acceleration.getX() - ACCELERATION);
	}
	else if(forces[RIGHT]){
		acceleration.setX(acceleration.getX() + ACCELERATION);
	}
	else{
		e->setVelocity(Vector2D(0.0f, e->getVelocity().getY()));
	}

	Vector2D vel = e->getVelocity() + acceleration*timeStep;
	e->setVelocity(vel);
}


void PhysicsManager::UpdateVelocityDir(Entity *e, const Vector2D &dir){
	Vector2D uDir = dir.makeUnitVector2D();
	//cout << uDir << endl;
	if(uDir.getX() > 0){
		uDir.setX(ACCELERATION);
	}
	else if(uDir.getX() < 0){
		uDir.setX(-ACCELERATION);
	}
	else{
		e->setVelocity(Vector2D(0.0f, e->getVelocity().getY()));
	}

	if(uDir.getY() > 0){
		uDir.setY(ACCELERATION);
	}
	else if(uDir.getY() < 0){
		uDir.setY(-ACCELERATION);
	}
	else{
		e->setVelocity(Vector2D(e->getVelocity().getX(), 0.0f));
	}
	//cout << "Dir: "<<uDir << endl;
	Vector2D vel = e->getVelocity() + uDir*timeStep;
	//cout << "New v: " << vel.magnitude() << endl;
	e->setVelocity(vel);
}


void PhysicsManager::UpdateEntityPos(Entity *e){
	Vector2D pos = e->getPosition() + e->getVelocity()*timeStep;
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


void PhysicsManager::handleEntityCollision(Entity *eHitting, Entity *eHit){
	Vector2D normal = eHitting->getVelocity().makeUnitVector2D();
	Vector2D netVelocity = eHitting->getVelocity() - eHit->getVelocity();//eHit->getVelocity() - eHitting->getVelocity();

	Vector2D normalVelocity = normal * Vector2D::dotProduct(netVelocity, normal);


	float jNumerator = -(1 + ELASTICITY) * Vector2D::dotProduct(netVelocity, normal);
	float jDenominator = Vector2D::dotProduct(normal, (normal * ((1.0f / eHitting->getMass()) + (1.0f / eHit->getMass()))));

	if(jDenominator <= 0.0f){
		return;
	}

	float J = jNumerator / jDenominator;

	eHitting->setVelocity(eHitting->getVelocity() + (normal * (J / eHitting->getMass())));
	eHit->setVelocity(eHit->getVelocity() - (normal * (J / eHit->getMass())));


	UpdateEntityPos(eHit);
	UpdateEntityPos(eHitting);

	
	
}


void PhysicsManager::handleWallCollision(Entity *eHitting){
	Vector2D normal = eHitting->getVelocity().makeUnitVector2D();
	Vector2D netVelocity = eHitting->getVelocity();

	Vector2D normalVelocity = normal * Vector2D::dotProduct(netVelocity, normal);


	float jNumerator = (-1.0f * (1.0f + ELASTICITY)) * Vector2D::dotProduct(netVelocity, normal);
	float jDenominator = Vector2D::dotProduct(normal, (normal * ((1.0f / eHitting->getMass()) + 1.0f)));

	if(jDenominator <= 0.0f){
		return;
	}

	float J = jNumerator / jDenominator;

	eHitting->setVelocity((/*eHitting->getVelocity() + */(normal * (J / eHitting->getMass()))) * 5.5f);

	UpdateEntityPos(eHitting);
}