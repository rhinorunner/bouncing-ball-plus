#include <iostream>
#include <vector>
#include <thread>
#include <SDL.h>
// for some reason this is needed so that it works
// idk just dont touch it
#undef main
#include "lib.hpp"
#include "ent.hpp"

// R = set all ent positions to middle of screen
// C = clear screen

int main() 
{
	BetterRand rand;
	ENTS = {};
	// append ENTS with random ents
	for (int i = 0; i < 1; i++) {
		ENTS.push_back
		(
			Ent
			(
				
(R_SCREENWIDTH / 2),
(R_SCREENHEIGHT / 2),
((rand.genRand() % 360)),
(4),
{
	255,
	255,
	255
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
			float midX = R_SCREENWIDTH / 2, midY = R_SCREENHEIGHT / 2;
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			case SDLK_r:
				// reset all ent positions to middle of the screen
				for (uint16_t i = 0; i < ENTS.size(); ++i) {
					ENTS[i].X = midX;
					ENTS[i].Y = midY;
				}
				break;
			case SDLK_c:
				SDL_RenderClear(R_RENDERER);
				break;
			}
		}
		std::vector<std::thread> threads;
		// entity loop
		for (uint16_t i = 0; i < ENTS.size(); ++i) 
		{
			// update and collision detection
			auto next = ENTS[i].nextUpdate(deltaTime);
			// for sprite collision calculation, added to coordinates
			uint16_t rightSide  = (ENTS[i].useSprite ? ENTS[i].sprite[0].size() : 0);
			uint16_t bottomSide = (ENTS[i].useSprite ? ENTS[i].sprite   .size() : 0);
			
			// too far right
			if (next.first + rightSide > R_SCREENWIDTH) {
				ENTS[i].reverseAngle(true);
			}
			// too far left
			if (next.first < 0) {
				ENTS[i].reverseAngle(true);
			}
			// too far down
			if (next.second + bottomSide > R_SCREENHEIGHT) {
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
			// blit pixels for ent sprite
			if (ENTS[i].useSprite) {
				for (uint16_t y = 0; y < ENTS[i].sprite.size(); ++y)
				{
					for (uint16_t x = 0; x < ENTS[i].sprite[y].size(); ++x) 
					{
						// set the color as defined in the key
						RGB_t setColor = {255,255,255};
						for (uint16_t C = 0; C < ENTS[i].colorKey.size(); ++C) 
						{
							if (ENTS[i].sprite[y][x] == ENTS[i].colorKey[C].first)
								setColor = ENTS[i].colorKey[C].second;
						}
						SDL_SetRenderDrawColor(
							R_RENDERER,
							setColor.R,
							setColor.G,
							setColor.B,
							255
						);
						// draw the point
						SDL_RenderDrawPoint(
							R_RENDERER, 
							(uint16_t)ENTS[i].X + x,
							(uint16_t)ENTS[i].Y + y
						);					
					}
				}
			}
		}
		// present render
		SDL_RenderPresent(R_RENDERER);
		SDL_SetRenderDrawColor(R_RENDERER, R_BACKCOLOR.R, R_BACKCOLOR.G, R_BACKCOLOR.B, 255);
		if (!R_NOCLEAR) SDL_RenderClear(R_RENDERER);
		//SDL_Delay(R_FRAMEDELAY);

		timeOld = timeNew;
	}
	
	// gives a fucking stupid "potentially uninitialized local pointer variable" error so just keep it out
	//SDL_DestroyRenderer(R_RENDERER);
	SDL_DestroyWindow(R_WINDOW);
	SDL_Quit();

	return 0;
}