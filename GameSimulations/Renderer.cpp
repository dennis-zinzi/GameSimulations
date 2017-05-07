#include "Renderer.h"

Renderer::Renderer(){
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_CreateWindow("SDL Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(screen, -1, 0);
	context = SDL_GL_CreateContext(screen);
	IMG_Init(IMG_INIT_JPG);
	IMG_Init(IMG_INIT_PNG);

	map = new Map();
}

Renderer::~Renderer(){
	SDL_Quit();
}


void Renderer::RenderScene(float msec){
	SDL_SetRenderDrawColor(renderer, 79, 79, 79, 255);
	SDL_RenderClear(renderer);

	DrawMap();

	//SDL update render	
	SDL_RenderPresent(renderer);

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
						return false;

					//case SDLK_w:
					//	Player->MoveForward();
					//	break;
					//case SDLK_s:
					//	Player->MoveBackward();
					//	break;
					//case SDLK_a:
					//	Player->MoveLeft();
					//	break;
					//case SDLK_d:
					//	Player->MoveRight();
					//	break;
					//case SDLK_p:
					//	Player->ShowControls();
					//	break;
					default:
						break;
				}
				break;
			}
		}
	}

	//Player->NoMovement();

	return true;
}

void Renderer::DrawMap(){
	for(int x = 0; x < 20; x++){
		for(int y = 0; y < 20; y++){
				Tile t = map->GetTiles()[x][y];

				SDL_Rect rect;
				rect.x = t.center.getX();
				rect.y = t.center.getY();
				rect.h = 40;
				rect.w = 40;

				int red, green, blue;
				switch(t.type){
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
