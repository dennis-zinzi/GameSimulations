/**
* Manages Flockign properties of Entities
*/
#pragma once

#include "Entity.h"
#include "Vector2D.h"

#include <vector>
#include "common.h"

using std::vector;

#define BOID_COHESION 0.01f
#define BOID_SEPARATION 25.0f
#define ALIGNMENT_FACTOR 0.125f
#define GOAL_TEND 0.5f


class BoidFlock{
	public:
		BoidFlock(vector<Entity*> boids, Entity *player);

		Vector2D UpdateBoid(Entity *e);
		inline void SetPlayerPos(Vector2D pos){
			playerPos = pos;
		}

		inline void NullPlayer(){
			player = nullptr;
		}

	private:
		Vector2D CalculateBoidCenter(Entity *e);
		Vector2D CalculateBoidSeperation(Entity *e);
		Vector2D CalculateBoidVelocity(Entity *e);
		Vector2D TendToPlayer(Entity *e);
		void LimitSpeed(Entity *e);

		vector<Entity*> boids;
		Entity *player;
		Vector2D playerPos;
};