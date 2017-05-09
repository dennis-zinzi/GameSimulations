#pragma once

#include "Entity.h"
#include "Vector2D.h"

#include <vector>
#include "common.h"

using std::vector;

#define BOID_COHESION 0.05f
#define BOID_SEPARATION 1.0f
#define ALIGNMENT_FACTOR 0.05f
#define GOAL_TEND 0.5f


class BoidFlock{
	public:
		BoidFlock(vector<Entity*> boids, Entity *player);

		Vector2D UpdateBoid(Entity *e);

	private:
		Vector2D CalculateBoidCenter(Entity *e);
		Vector2D CalculateBoidSeperation(Entity *e);
		Vector2D CalculateBoidVelocity(Entity *e);
		Vector2D TendToPlayer(Entity *e);
		void LimitSpeed(Entity *e);

		vector<Entity*> boids;
		Entity *player;
};