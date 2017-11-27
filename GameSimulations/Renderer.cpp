#include "Renderer.h"

Renderer::Renderer(Map *map){
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("SDL Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, 0);
	context = SDL_GL_CreateContext(window);
	IMG_Init(IMG_INIT_JPG);
	IMG_Init(IMG_INIT_PNG);
	
	screen = SDL_GetWindowSurface(window);

	this->map = map;
	lastUpdate = SDL_GetTicks();
}

Renderer::~Renderer(){
	for(auto tex : textures){
		SDL_DestroyTexture(tex.tex);
	}

	IMG_Quit();
	SDL_Quit();
}


void Renderer::RenderEntity(Entity *e){
	SDL_Rect rect;
	rect.x = e->getXPosition();
	rect.y = e->getYPosition();
	rect.h = ENTITY_HEIGHT;
	rect.w = ENTITY_WIDTH;
	SDL_RenderCopy(renderer, e->getTexture(), nullptr, &rect);
}


void Renderer::RenderScene(float msec, vector<Entity*> entities, Entity *player){
	//SDL_SetRenderDrawColor(renderer, 79, 79, 79, 255);
	SDL_RenderClear(renderer);

	//Draw Map
	DrawMap();

	for(auto e : entities){
		RenderEntity(e);
	}

	if(player){
		RenderEntity(player);
	}

	//SDL update render	
	SDL_RenderPresent(renderer);
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
