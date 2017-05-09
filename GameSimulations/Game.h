#pragma once

#include "common.h"
#include "Renderer.h"
#include "PhysicsManager.h"
#include "Entity.h"
#include "BoidFlock.h"
#include "Map.h"

class Game{
	public:
		Game(Renderer *r, PhysicsManager *physics);

		void RenderScene(Renderer r, float msec);
		void UpdateEntities();
		bool CheckInputs();

	private:
		vector<Entity*> entities;
		Entity *player;
		BoidFlock *flock;
		Map *map;

		PhysicsManager *physics;
		Renderer *renderer;

		void CreateEntities();

};