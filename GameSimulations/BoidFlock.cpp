#include "BoidFlock.h"

BoidFlock::BoidFlock(vector<Entity*> boids, Entity *player){
	this->boids = boids;
	this->player = player;
}




Vector2D BoidFlock::UpdateBoid(Entity *e){
	Vector2D center = CalculateBoidCenter(e),
		separation = CalculateBoidSeperation(e),
		vel = CalculateBoidVelocity(e);
		//tendency = TendToPlayer(e);

	Vector2D v = e->getVelocity() + center + vel;
	if(player){
		v += separation;
	}

	return (v / v.magnitude()) * MAX_VEL;
}


/* Boid Rules */
Vector2D BoidFlock::CalculateBoidCenter(Entity *e){
	if(player){
		return (player->getPosition() - e->getPosition()) * BOID_COHESION;
	}
	else{
		return (playerPos - e->getPosition()) * BOID_COHESION;
	}
}


Vector2D BoidFlock::CalculateBoidSeperation(Entity *e){
	Vector2D separation;

	for(auto b : boids){
		if(b == e){
			continue;
		}

		if((b->getPosition() - e->getPosition()).magnitude() < BOID_SEPARATION){
			separation -= b->getPosition() - e->getPosition();
		}
	}

	return separation;
}


Vector2D BoidFlock::CalculateBoidVelocity(Entity *e){
	Vector2D vel;

	for(auto b : boids){
		if(b == e){
			continue;
		}

		vel += b->getVelocity();
	}

	vel /= (boids.size() - 1.0f);

	return (vel - e->getVelocity()) * ALIGNMENT_FACTOR;
}


void BoidFlock::LimitSpeed(Entity *e){
	if(e->getVelocity().magnitude() > MAX_VEL){
		Vector2D vel = (e->getVelocity() / e->getVelocity().magnitude()) * MAX_VEL;
		e->setVelocity(vel);
	}
}


Vector2D BoidFlock::TendToPlayer(Entity *e){
	if(player){
		return (player->getPosition() - e->getPosition()) * GOAL_TEND;
	}

	return (playerPos - e->getPosition())  * GOAL_TEND;
}