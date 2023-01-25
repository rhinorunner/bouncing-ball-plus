#include <iostream>
#include <vector>
#include <thread>
#include <SDL.h>
// for some reason this is needed so that it works
// idk just dont touch it
#undef main
#include "lib.hpp"
#include "ent.hpp"

int main() 
{
	BetterRand rand;
	ENTS = {};
	// append ENTS with random ents
	for (int i = 0; i < 100; i++) {
		ENTS.push_back
		(
			Ent
			(
				(rand.genRand() % R_SCREENWIDTH),
				(rand.genRand() % R_SCREENHEIGHT),
				((rand.genRand() % 3600) / 10),
				((rand.genRand() % 150) / 10) + 1,
				{
					(uint8_t)(rand.genRand() % 256),
					(uint8_t)(rand.genRand() % 256),
					(uint8_t)(rand.genRand() % 256)
				}
			)
		);
	}

	// the window!
	SDL_Window* R_WINDOW = NULL;

	// renderer
	SDL_Renderer* R_RENDERER;

	// initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return 0;
	}
	//R_WINDOW = SDL_CreateWindow("Raycasting", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, R_SCREENWIDTH, R_SCREENHEIGHT, SDL_WINDOW_SHOWN);
		
	SDL_CreateWindowAndRenderer(R_SCREENWIDTH, R_SCREENHEIGHT, 0, &R_WINDOW, &R_RENDERER);
	if (R_WINDOW == NULL) {
		std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		return 0;
	}
	SDL_SetRenderDrawColor(R_RENDERER, 0, 0, 0, 0);
	SDL_RenderClear(R_RENDERER);

	SDL_Event e;
	bool quit = false;
	clock_t timeOld = clock();
	clock_t timeNew = clock();
	float deltaTime = 0;
	float time_calib = .05;
	
	while(quit == false) 
	{
		timeNew = clock();
		deltaTime = (timeNew - timeOld) * time_calib;

		SDL_PollEvent(&e);
		
		// close window button
		if (e.type == SDL_QUIT) quit = true; 
					
		// key press
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			case SDLK_r:
				// reset all ent positions to middle of the screen
				float midX = R_SCREENWIDTH / 2, midY = R_SCREENHEIGHT / 2;
				for (uint8_t i = 0; i < ENTS.size(); ++i) {
					ENTS[i].X = midX;
					ENTS[i].Y = midY;
				}
				break;
			}
		}
		std::vector<std::thread> threads;
		// entity loop
		for (uint8_t i = 0; i < ENTS.size(); ++i) 
		{
			// update and collision detection
			auto next = ENTS[i].nextUpdate(deltaTime);
			// too far right
			if (next.first > R_SCREENWIDTH) {
				ENTS[i].reverseAngle(true);
			}
			// too far left
			if (next.first < 0) {
				ENTS[i].reverseAngle(true);
			}
			// too far down
			if (next.second > R_SCREENHEIGHT) {
				ENTS[i].reverseAngle(false);
			}
			// too far up
			if (next.second < 0) {
				ENTS[i].reverseAngle(false);
			}

			ENTS[i].update(deltaTime);
				
			SDL_SetRenderDrawColor(
				R_RENDERER, 
				ENTS[i].color.R,
				ENTS[i].color.G,
				ENTS[i].color.B,
				255
			);
			SDL_RenderDrawPoint(R_RENDERER, (uint16_t)ENTS[i].X, (uint16_t)ENTS[i].Y);
		}
		// present render
		SDL_RenderPresent(R_RENDERER);
		SDL_SetRenderDrawColor(R_RENDERER, R_BACKCOLOR.R, R_BACKCOLOR.G, R_BACKCOLOR.B, 255);
		//SDL_RenderClear(R_RENDERER);
		//SDL_Delay(R_FRAMEDELAY);

		timeOld = timeNew;
	}
	
	// gives a fucking stupid "potentially uninitialized local pointer variable" error so just keep it out
	//SDL_DestroyRenderer(R_RENDERER);
	SDL_DestroyWindow(R_WINDOW);
	SDL_Quit();

	return 0;
}