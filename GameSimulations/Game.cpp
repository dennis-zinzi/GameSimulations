#include "Game.h"

Game::Game(Renderer * r, PhysicsManager * physics){
	renderer = r;
	this->physics = physics;
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
							break;

						default:
							break;
					}
					break;
				}
		}
	}

	const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);

	bool directions[4];
	for(int i = 0; i < 4; i++){
		directions[i] = false;
	}

	// Move player
	if((keyboard_state[SDL_SCANCODE_W] && !keyboard_state[SDL_SCANCODE_S])
		|| (keyboard_state[SDL_SCANCODE_UP] && !keyboard_state[SDL_SCANCODE_DOWN])){
		//player->updateYPos(-0.1f);
		directions[UP] = true;
		//playerTex = renderer->LoadTex("player_b.png");
	}
	else if((keyboard_state[SDL_SCANCODE_S] && !keyboard_state[SDL_SCANCODE_W])
		|| (keyboard_state[SDL_SCANCODE_DOWN] && !keyboard_state[SDL_SCANCODE_UP])){
		//player->updateYPos(0.1f);
		directions[DOWN] = true;
		//playerTex = LoadTex("player_f.png");
	}

	if((keyboard_state[SDL_SCANCODE_D] && !keyboard_state[SDL_SCANCODE_A])
		|| (keyboard_state[SDL_SCANCODE_RIGHT] && !keyboard_state[SDL_SCANCODE_LEFT])){
		//player->updateXPos(0.1f);
		directions[RIGHT] = true;
		//playerTex = LoadTex("player_r.png");
	}
	else if((keyboard_state[SDL_SCANCODE_A] && !keyboard_state[SDL_SCANCODE_D])
		|| (keyboard_state[SDL_SCANCODE_LEFT] && !keyboard_state[SDL_SCANCODE_RIGHT])){
		//player->updateXPos(-0.1f);
		directions[LEFT] = true;
		//playerTex = LoadTex("player_l.png");
	}



	if(player->getCurrentTile().GetType() == TileType::WALL){
		physics->handleWallCollision(player);
	}


	physics->UpdateVelocity(player, directions);
	physics->UpdateEntityPos(player);

	/*if(n > 0){
	cout << "Colliding: " << n << endl << endl;
	}*/

	//cout << "Player Pos: " << player->getPosition() << endl;
	return true;
}

void Game::CreateEntities(){
	entities.clear();

	bool left = Utilities::RandomFloat(-1.0f, 1.0f) > 0.0f ? true : false;

	for(int i = 0; i < NUMOFENTITIES; i++){
		if(left){
			Vector3D pos(Utilities::RandomFloat(0.0f, 80.0f), Utilities::RandomFloat(0.0f, 80.0f), 0);
			entities.push_back(new Entity(pos, map));
		}
		else{
			Vector3D pos(Utilities::RandomFloat(680.0f, 760.0f), Utilities::RandomFloat(0.0f, 80.0f), 0);
			entities.push_back(new Entity(pos, map));
		}
	}

	if(left){
		Vector3D pos(Utilities::RandomFloat(0.0f, 80.0f), Utilities::RandomFloat(0.0f, 80.0f), 0);
		player->updatePos(pos);
	}
	else{
		Vector3D pos(Utilities::RandomFloat(680.0f, 760.0f), Utilities::RandomFloat(0.0f, 80.0f), 0);
		player->updatePos(pos);
	}

	flock = new BoidFlock(entities, player);
}

