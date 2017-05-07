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
		void UpdateEntityPos(Entity *e);

	private:
		vector<Entity*> entities;
		float timeStep;


};