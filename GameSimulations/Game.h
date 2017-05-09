#pragma once

#include "common.h"
#include "Renderer.h"
#include "PhysicsManager.h"
#include "Entity.h"
#include "BoidFlock.h"
#include "Map.h"

#define GOAL_POS Vector2D(440.0f, 760.0f)
#define BASE1_MIN_X 0.0f
#define BASE1_MAX_X 80.0f

#define BASE2_MIN_X 680.0f
#define BASE2_MAX_X 760.0f

#define BASE_MIN_Y 0.0f
#define BASE_MAX_Y 80.0f

class Game{
	public:
		Game(Renderer *r, PhysicsManager *physics, Map *map);

		void RenderScene(float msec);
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
		void InitJenkinsSquad();

};