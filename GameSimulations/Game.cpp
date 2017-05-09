#include "Game.h"

Game::Game(Renderer *r, PhysicsManager *physics, Map *map){
	renderer = r;
	this->physics = physics;
	this->map = map;
}

void Game::RenderScene(float msec){
	renderer->RenderScene(msec, entities, player);
}

void Game::UpdateEntities(){
	vector<int> indicies;
	int i = -1;

	for(auto e : entities){
		i++;
		if(e->getWin()){
			indicies.push_back(i);
			continue;
		}

		Vector2D vel;

		if(e->getPath().empty() && flock != nullptr){
			vel = flock->UpdateBoid(e);
		}
		else if(!e->getPath().empty() && e->getCurrentIndex() < e->getPath().size() - 1){
			vel = e->getPath()[e->getCurrentIndex() + 1] - e->getPosition();

			if(Vector2D::dist(e->getPath()[e->getCurrentIndex() + 1], e->getPosition()) < 25.0f){
				cout << e->getCurrentIndex() + 1 << "/" << e->getPath().size() << endl;
				e->setCurrentIndex(e->getCurrentIndex() + 1);

				//Decelerate AI to make them turn
				physics->UpdateVelocityDir(e, Vector2D());
			}
		}

		if(e->getCurrentTile().GetType() == TileType::WALL) {
			physics->handleWallCollision(e);
		}

		physics->UpdateVelocityDir(e, vel);
		physics->UpdateEntityPos(e);
	}

	for(auto index : indicies){
		if(index < entities.size()){
			entities.erase(entities.begin() + index);
		}
	}

	if(player && player->getWin()){
		if(flock){
			flock->SetPlayerPos(player->getPosition());
			flock->NullPlayer();
			delete player;
			player = nullptr;
		}
	}

}

bool Game::CheckInputs(){
	SDL_Event event;

	//Runs whilst there is an event being queued
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				return false;
			case SDL_KEYDOWN:
				{
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
						case SDLK_x:
							return false;
						case SDLK_k:
							CreateEntities();
							flock = new BoidFlock(entities, player);
							break;
						case SDLK_j:
							CreateEntities();
							InitJenkinsSquad();
							break;
						case SDLK_l:
							CreateEntities();
							InitTacticalSquad();
							break;
						default:
							break;
					}
					break;
				}
		}
	}

	if(player){
		const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);

		bool directions[4];
		for(int i = 0; i < 4; i++){
			directions[i] = false;
		}

		// Move player
		if((keyboard_state[SDL_SCANCODE_W] && !keyboard_state[SDL_SCANCODE_S])
			|| (keyboard_state[SDL_SCANCODE_UP] && !keyboard_state[SDL_SCANCODE_DOWN])){
			//Apply force upwards
			directions[UP] = true;

			player->setTexture(renderer->LoadTex("player_b.png"));
		}
		else if((keyboard_state[SDL_SCANCODE_S] && !keyboard_state[SDL_SCANCODE_W])
			|| (keyboard_state[SDL_SCANCODE_DOWN] && !keyboard_state[SDL_SCANCODE_UP])){
			//Apply force downwards
			directions[DOWN] = true;

			player->setTexture(renderer->LoadTex("player_f.png"));
		}

		if((keyboard_state[SDL_SCANCODE_D] && !keyboard_state[SDL_SCANCODE_A])
			|| (keyboard_state[SDL_SCANCODE_RIGHT] && !keyboard_state[SDL_SCANCODE_LEFT])){
			//Apply force rightwards
			directions[RIGHT] = true;
			player->setTexture(renderer->LoadTex("player_r.png"));
		}
		else if((keyboard_state[SDL_SCANCODE_A] && !keyboard_state[SDL_SCANCODE_D])
			|| (keyboard_state[SDL_SCANCODE_LEFT] && !keyboard_state[SDL_SCANCODE_RIGHT])){
			//Apply force leftwards
			directions[LEFT] = true;
			player->setTexture(renderer->LoadTex("player_l.png"));
		}


		if(player->getCurrentTile().GetType() == TileType::WALL){
			physics->handleWallCollision(player);
		}


		physics->UpdateVelocity(player, directions);
		physics->UpdateEntityPos(player);
	}

	return true;
}

void Game::CreateEntities(){
	entities.clear();

	//Randomly select what base to spawn entities in
	bool left = Utilities::RandomFloat(-1.0f, 1.0f) > 0.0f ? true : false;

	//Spawn the entities in selected base
	for(int i = 0; i < NUMOFENTITIES; i++){
		if(left){
			Vector2D pos(Utilities::RandomFloat(BASE1_MIN_X, BASE1_MAX_X), Utilities::RandomFloat(BASE_MIN_Y, BASE_MAX_Y));
			entities.push_back(new Entity(pos, renderer->LoadTex("ai_f.png"), map));
		}
		else{
			Vector2D pos(Utilities::RandomFloat(BASE2_MIN_X, BASE2_MAX_X), Utilities::RandomFloat(BASE_MIN_Y, BASE_MAX_Y));
			entities.push_back(new Entity(pos, renderer->LoadTex("ai_f.png"), map));
		}
	}

	//Create player if doesn't exist
	if(!player){
		player = new Entity(renderer->LoadTex("player_f.png"), map);
	}

	//Set player position in randomly selected base
	if(left){
		Vector2D pos(Utilities::RandomFloat(BASE1_MIN_X, BASE1_MAX_X), Utilities::RandomFloat(BASE_MIN_Y, BASE_MAX_Y));
		player->updatePos(pos);
	}
	else{
		Vector2D pos(Utilities::RandomFloat(BASE2_MIN_X, BASE2_MAX_X), Utilities::RandomFloat(BASE_MIN_Y, BASE_MAX_Y));
		player->updatePos(pos);
	}

}


void Game::InitJenkinsSquad(){
	for(auto e : entities){
		e->setPath(AStar::GetAStarPath(e->getPosition(), GOAL_POS, map->GetMapAsPathNodes()));
	}
}

void Game::InitTacticalSquad(){
	for(auto e : entities){
		//cout << AStar::GetClosestTacticalNode(e->getPosition(), map->GetMapAsPathNodes())->Position << endl;

		e->setPath(AStar::GetTacticalAStarPath(e->getPosition(), 
			AStar::GetClosestTacticalNode(e->getPosition(), map->GetMapAsPathNodes())->Position,
			map->GetMapAsPathNodes()));
	}
}
