#pragma once

#include "Entity.h"
#include "common.h"

#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

class PhysicsManager{
	public:
		PhysicsManager();
		void UpdatePhysics(float msec);
		void UpdateVelocity(Entity *e, bool *forces);
		void UpdateVelocityDir(Entity *e, const Vector2D &dir);
		void UpdateEntityPos(Entity *e);

		bool IsEntityCollidingWithEntity(Entity *colliding, Entity *e);
		void handleEntityCollision(Entity *eHitting, Entity *eHit);
		void handleWallCollision(Entity *eHitting);

	private:
		vector<Entity*> entities;
		float timeStep;


};