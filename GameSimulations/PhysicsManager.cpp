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
	cout << "New v: " << vel.magnitude() << endl;
	e->setVelocity(vel);
}


void PhysicsManager::UpdateEntityPos(Entity *e){
	Vector3D pos = e->getPosition() + e->getVelocity()*timeStep;
	e->updatePos(pos);
}