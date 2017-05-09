#include "Renderer.h"

Renderer::Renderer(){
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("SDL Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, 0);
	context = SDL_GL_CreateContext(window);
	IMG_Init(IMG_INIT_JPG);
	IMG_Init(IMG_INIT_PNG);
	
	screen = SDL_GetWindowSurface(window);

	p = new PhysicsManager();

	map = new Map();
	player = new Entity(30, 30, map);

	playerTex = LoadTex("player_f.png");
	aiTex = LoadTex("ai_f.png");
}

Renderer::~Renderer(){
	for(auto tex : textures){
		SDL_DestroyTexture(tex.tex);
	}

	IMG_Quit();
	SDL_Quit();
}


void Renderer::CreateEntities(){
	ais.clear();

	bool left = Utilities::RandomFloat(-1.0f, 1.0f) > 0.0f ? true : false;

	for(int i = 0; i < NUMOFENTITIES; i++){
		if(left){
			Vector3D pos(Utilities::RandomFloat(0.0f, 80.0f), Utilities::RandomFloat(0.0f, 80.0f), 0);
			ais.push_back(new Entity(pos, map));
		}
		else{
			Vector3D pos(Utilities::RandomFloat(680.0f, 760.0f), Utilities::RandomFloat(0.0f, 80.0f), 0);
			ais.push_back(new Entity(pos, map));
		}
	}

	if(!player){
		player = new Entity(map);
	}

	if(left){
		Vector3D pos(Utilities::RandomFloat(0.0f, 80.0f), Utilities::RandomFloat(0.0f, 80.0f), 0);
		player->updatePos(pos);
	}
	else{
		Vector3D pos(Utilities::RandomFloat(680.0f, 760.0f), Utilities::RandomFloat(0.0f, 80.0f), 0);
		player->updatePos(pos);
	}

}

void Renderer::RenderEntity(Entity *e, string texfile){
	SDL_Rect rect;
	rect.x = e->getXPosition();
	rect.y = e->getYPosition();
	rect.h = ENTITY_HEIGHT;
	rect.w = ENTITY_WIDTH;
	SDL_RenderCopy(renderer, LoadTex(texfile), nullptr, &rect);
}


void Renderer::RenderScene(float msec){
	//SDL_SetRenderDrawColor(renderer, 79, 79, 79, 255);
	SDL_RenderClear(renderer);


	DrawMap();

	vector<int> indicies;
	int i = -1;

	for(auto ai : ais){
		i++;
		if(ai->getWin()){
			indicies.push_back(i);
			continue;
		}

		Vector2D vel;

		if(ai->getPath().empty() && flock != nullptr){
			vel = flock->UpdateBoid(ai);
		}
		else if(!ai->getPath().empty()){
			vel = ai->getPath()[ai->getCurrentIndex() + 1] - ai->getPosition();

			if(Vector2D::dist(ai->getPath()[ai->getCurrentIndex() + 1], ai->getPosition()) < 25.0f){
				cout << ai->getCurrentIndex() + 1 << "/" << ai->getPath().size() << endl;
				ai->setCurrentIndex(ai->getCurrentIndex() + 1);
				//Decelerate AI to make them turn
				p->UpdateVelocityDir(ai, Vector2D());
			}
		}

		if (ai->getCurrentTile().GetType() == TileType::WALL) {
			p->handleWallCollision(ai);
		}

		p->UpdateVelocityDir(ai, vel);
		p->UpdateEntityPos(ai);

		SDL_Rect arect;
		arect.x = ai->getXPosition();
		arect.y = ai->getYPosition();
		arect.h = ENTITY_HEIGHT;
		arect.w = ENTITY_WIDTH;
		SDL_RenderCopy(renderer, aiTex, nullptr, &arect);
	}

	for(auto index : indicies){
		ais.erase(ais.begin() + index);
	}

	if(player && player->getWin()){
		if(flock){
			flock->SetPlayerPos(player->getPosition());
			flock->NullPlayer();
			delete player;
			player = nullptr;
		}
	}
	else if(player){
		//Render player
		SDL_Rect rect;
		rect.x = player->getXPosition();
		rect.y = player->getYPosition();
		rect.h = ENTITY_HEIGHT;
		rect.w = ENTITY_WIDTH;

		SDL_RenderCopy(renderer, playerTex, nullptr, &rect);
	}


	//SDL update render	
	SDL_RenderPresent(renderer);

	//cout << "T: " << 1000/FRAME_RATE << " FPS: " << (SDL_GetTicks() - msec) << endl;

	//Cap frame rate at 60 FPS
	if(1000 / FRAME_RATE > SDL_GetTicks() - msec){
		SDL_Delay((Uint32)((1000 / FRAME_RATE) - (SDL_GetTicks() - msec)));
	}
}

bool Renderer::CheckInputs(){
	SDL_Event event;

	//Runs whilst there is an event being queued
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT:
				return false;
			case SDL_KEYDOWN: {
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
					case SDLK_x:
						return false;
					case SDLK_k:
						CreateEntities();
						flock = new BoidFlock(ais, player);
						break;
					case SDLK_j:
						CreateEntities();
						InitJenkinsSquad();
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
		//Apply force upwards
		directions[UP] = true;

		playerTex = LoadTex("player_b.png");
	}
	else if((keyboard_state[SDL_SCANCODE_S] && !keyboard_state[SDL_SCANCODE_W])
		|| (keyboard_state[SDL_SCANCODE_DOWN] && !keyboard_state[SDL_SCANCODE_UP])){
		//Apply force downwards
		directions[DOWN] = true;

		playerTex = LoadTex("player_f.png");
	}

	if((keyboard_state[SDL_SCANCODE_D] && !keyboard_state[SDL_SCANCODE_A])
		|| (keyboard_state[SDL_SCANCODE_RIGHT] && !keyboard_state[SDL_SCANCODE_LEFT])){
		//Apply force rightwards
		directions[RIGHT] = true;
		playerTex = LoadTex("player_r.png");
	}
	else if((keyboard_state[SDL_SCANCODE_A] && !keyboard_state[SDL_SCANCODE_D])
		|| (keyboard_state[SDL_SCANCODE_LEFT] && !keyboard_state[SDL_SCANCODE_RIGHT])){
		//Apply force leftwards
		directions[LEFT] = true;
		playerTex = LoadTex("player_l.png");
	}


	if(player){
		if(player->getCurrentTile().GetType() == TileType::WALL){
			p->handleWallCollision(player);
		}


		p->UpdateVelocity(player, directions);
		p->UpdateEntityPos(player);
	}

	return true;
}

void Renderer::DrawMap(){
	for(int x = 0; x < 20; x++){
		for(int y = 0; y < 20; y++){
				Tile t = map->GetTiles()[x][y];

				SDL_Rect rect;
				rect.x = t.GetCenter().getX();
				rect.y = t.GetCenter().getY();
				rect.h = 40;
				rect.w = 40;

				int red, green, blue;
				switch(t.GetType()){
					case BASE:
						red = 255;
						green = 255;
						blue = 204;
						break;
					case OPEN:
						red = 226;
						green = 239;
						blue = 218;
						break;
					case COVERED:
						red = 169;
						green = 208;
						blue = 142;
						break;
					case BRIDGE:
						red = 131;
						green = 60;
						blue = 12;
						break;
					case FOREST:
						red = 55;
						green = 86;
						blue = 35;
						break;
					case RIVER:
						red = 91;
						green = 155;
						blue = 213;
						break;
					case GATE:
						red = 198;
						green = 89;
						blue = 17;
						break;
					case WALL:
						red = 165;
						green = 165;
						blue = 165;
						break;
					case CASTLE:
						red = 231;
						green = 230;
						blue = 230;
						break;
				}

				SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
				SDL_RenderFillRect(renderer, &rect);
		}
	}
}


SDL_Texture* Renderer::LoadTex(string texfile){
	//Check if texture already loaded, and return it if true
	for(auto t : textures){
		if(t.name == texfile){
			return t.tex;
		}
	}

	string texturePath = IMAGES_PATH + texfile;

	SDL_Texture *texture = nullptr;

	SDL_Surface *surface = IMG_Load(texturePath.c_str());
	if(!surface){
		cout << "ERROR: couldn't find " << texfile << endl;
		return nullptr;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if(!texture){
		cout << "ERROR: problem loading " << texfile << endl;
	}

	SDL_FreeSurface(surface);

	textures.push_back(Texture {texfile, texture});
	return texture;
}


void Renderer::InitJenkinsSquad(){
	for(auto ai : ais){
		ai->setPath(AStar::GetAStarPath(ai->getPosition(), Vector2D(440.0f, 760.0f), map->GetMapAsPathNodes()));
	}
}