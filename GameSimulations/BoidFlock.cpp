#include "BoidFlock.h"

BoidFlock::BoidFlock(vector<Entity*> boids, Entity *player){
	this->boids = boids;
	this->player = player;
}




Vector2D BoidFlock::UpdateBoid(Entity *e){
	Vector2D center = CalculateBoidCenter(e),
		separation = CalculateBoidSeperation(e),
		vel = CalculateBoidVelocity(e),
		tendency = TendToPlayer(e);
		
	if(Vector2D::distance(e->getPosition(), player->getPosition()) > 20.0f){
		return center*-1.0f;// + separation + vel + tendency;
	}
	else if(Vector2D::distance(e->getPosition(), player->getPosition()) < -20.0f){
		return (center*1.0f);// + separation + vel + tendency) * -1.0;
	}

	return center*-1.0f;
	//return /*player->getVelocity() * */(center + separation + vel + tendency);
}


/* Boid Rules */
Vector2D BoidFlock::CalculateBoidCenter(Entity *e){
	return (e->getPosition() - player->getPosition()) * BOID_COHESION;
	//return (player->getPosition() - e->getPosition()) * BOID_COHESION;
}


Vector2D BoidFlock::CalculateBoidSeperation(Entity *e){
	Vector2D separation;

	for(auto b : boids){
		if(b == e){
			continue;
		}

		if(abs(Vector2D::distance(b->getPosition(), e->getPosition())) < BOID_SEPARATION){
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

	vel / (boids.size() - 1);

	return (vel - e->getVelocity()) * ALIGNMENT_FACTOR;
}


void BoidFlock::LimitSpeed(Entity *e){
	if(e->getVelocity().magnitude() > MAX_VEL){
		Vector2D vel = (e->getVelocity() / e->getVelocity().magnitude()) * MAX_VEL;
		e->setVelocity(vel);
	}
}


Vector2D BoidFlock::TendToPlayer(Entity *e){
	return (player->getPosition()) * GOAL_TEND;
}