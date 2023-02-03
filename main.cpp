#include <iostream>
#include <vector>
#include <thread>
#include <fstream>
#include <string>
#include <SDL.h>
// for some reason this is needed so that it works
// idk just dont touch it
#undef main
#include "lib.hpp"
#include "ent.hpp"

int main() 
{
	BetterRand rand;

	// append ENTS with random ents
	bool OD = false;
	for (int i = 0; i < 500; i++) {
		Ent new_ent
		(
			((rand.genRand() % R_SCREENWIDTH)),
			((rand.genRand() % R_SCREENHEIGHT)),
			(((i%16) % (360 / 16)) * (360 / 16)),
			((float)(rand.genRand() % 10)/10)+2,
			{
				(uint8_t)((rand.genRand() % 10)+90+(i % 2 ? 100 : 0)),
				(uint8_t)((rand.genRand() % 10)+90+(i % 2 ? 100 : 0)),
				(uint8_t)((rand.genRand() % 10)+90+(i % 2 ? 0 : 100))
			}
		);

		// new_ent.useSprite = 1;
		// fill sprite with a square of random colors
		for (uint16_t C = 0; C < 3; ++C) 
		{
			std::vector<char> filler {};
			for (uint16_t R = 0; R < 3; ++R) 
				filler.push_back('#');
			new_ent.sprite.push_back({filler});
		}
		new_ent.colorKey.push_back({'#',new_ent.color});
		

		// set trail color to ent color, slowly fading
		// fade to black
		uint16_t trailStep = 255/new_ent.trailLife;
		if (trailStep <= 0) trailStep = 2;
		for (uint16_t Q = 1; Q < new_ent.trailLife; ++Q) 
		{
			if (OD)
			std::cout
				<< "R: "
				<< (int16_t)new_ent.color.R
				<< " - ("
				<< trailStep
				<< " * "
				<< Q
				<< ") = "
				<< (int16_t)(new_ent.color.R - (trailStep * Q))
				<< '\n';
			int16_t R = new_ent.color.R - (trailStep * Q);
			R=(R>255)?255:R;R=(R<0)?0:R;
			int16_t G = new_ent.color.G - (trailStep * Q);
			G=(G>255)?255:G;G=(G<0)?0:G;
			int16_t B = new_ent.color.B - (trailStep * Q);
			B=(B>255)?255:B;B=(B<0)?0:B;
			
			//new_ent.trailColors.push_back({(uint8_t)R,(uint8_t)G,(uint8_t)B});
			new_ent.trailColors.insert(
				new_ent.trailColors.begin(), 
				{
					(uint8_t)R,
					(uint8_t)G,
					(uint8_t)B
				}
			);
			if (OD)
			std::cout 
				<< '['
				<< (uint16_t)((uint8_t)R)
				<< ','
				<< (uint16_t)((uint8_t)G)
				<< ','
				<< (uint16_t)((uint8_t)B)
				<< ']'
				<< '\n';
			if ((R+G+B) < 10) break;
		}
		
		// use file sprite?
		if (new_ent.useSprite == 2)
		{
			std::ifstream infile(STR_PATH + "sprites/" + new_ent.spriteFile);
			std::string line;
			std::vector<std::vector<char>> temp{{}};

			while (std::getline(infile, line)) {
				std::vector<char> row;
				for (char& c : line) {
					row.push_back(c);
				}

				temp.push_back(row);
			}
			new_ent.sprite = temp;
		}
		ENTS.push_back(new_ent);
		OD = false;
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
	bool turningLeft = false;
	bool turningRight = false;
	
	while(!quit) 
	{
		if (!R_USEFRAMEDELAY) {
			timeNew = clock();
			deltaTime = (timeNew - timeOld) * time_calib;
		}

		else {
			SDL_Delay(R_FRAMEDELAY);
			deltaTime = R_DELTAREPLACE;
		}

		SDL_PollEvent(&e);
		
		// close window button
		if (e.type == SDL_QUIT) quit = true; 
					
		// key press
		if (e.type == SDL_KEYDOWN) 
		{
			float midX = R_SCREENWIDTH / 2, midY = R_SCREENHEIGHT / 2;
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;

			// set all ent positions to middle of the screen
			case SDLK_KP_MULTIPLY:
				for (uint16_t i = 0; i < ENTS.size(); ++i) {
					ENTS[i].X = midX;
					ENTS[i].Y = midY;
				}
				break;
			// set all ent positions to random positions
			case SDLK_KP_DIVIDE:
				for (uint16_t i = 0; i < ENTS.size(); ++i) {
					ENTS[i].X = rand.genRand() % R_SCREENWIDTH;
					ENTS[i].Y = rand.genRand() % R_SCREENHEIGHT;
				}
				break;
			// set all ent angles to random
			case SDLK_KP_9:
				for (uint16_t i = 0; i < ENTS.size(); ++i) {
					ENTS[i].angle = rand.genRand() % 360;
				}
				break;

			// change angle by +1
			case SDLK_LEFT:
				turningLeft = true;
				break;
			// change angle by -1
			case SDLK_RIGHT:
				turningRight = true;
				break;

			// clear screen (only works with no clear)
			case SDLK_KP_0:
				SDL_RenderClear(R_RENDERER);
				break;

			// pause
			case SDLK_KP_PERIOD:
				while (true) {
					SDL_PollEvent(&e);
					if (e.type == SDL_KEYDOWN) {
						if (e.key.keysym.sym == SDLK_KP_PERIOD)  break;
						if (e.key.keysym.sym == SDLK_ESCAPE) { quit = true; break; }
					}
					if (e.type == SDL_QUIT) quit = true; 
				}
				// make sure deltatime isnt messed up
				if (R_USEFRAMEDELAY) timeNew = clock();
				break;

			// increase ent brightness
			case SDLK_KP_MINUS:
				if (R_ENTBRIGHTNESS > 0) R_ENTBRIGHTNESS -= R_BRTSTEP;
				break;
			// decrease ent brightness
			case SDLK_KP_PLUS:
				if (R_ENTBRIGHTNESS < 255) R_ENTBRIGHTNESS += R_BRTSTEP;
				break;
			}
		}
		if (e.type == SDL_KEYUP) {
			switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				turningLeft = false;
				break;
			case SDLK_RIGHT:
				turningRight = false;
				break;
			}
		}

		std::vector<std::thread> threads;
		// entity loop
		for (uint16_t i = 0; i < ENTS.size(); ++i) 
		{
			if (turningLeft) {
				ENTS[i].angle -= R_ANGLESTEP;
			}
			if (turningRight) {
				ENTS[i].angle += R_ANGLESTEP;
			}

			// update and collision detection
			auto next = ENTS[i].nextUpdate(deltaTime);
			// for sprite collision calculation, added to coordinates
			uint16_t rightSide  = (ENTS[i].useSprite ? ENTS[i].sprite[0].size() : 0);
			uint16_t bottomSide = (ENTS[i].useSprite ? ENTS[i].sprite   .size() : 0);
			
			// too far right
			if (next.first + rightSide > R_SCREENWIDTH) {
				if (!R_PHYSTYPE) ENTS[i].reverseAngle(true);
				else if (R_PHYSTYPE == 1) ENTS[i].X = 1;
			}
			// too far left
			if (next.first < 0) {
				if (!R_PHYSTYPE) ENTS[i].reverseAngle(true);
				else if (R_PHYSTYPE == 1) ENTS[i].X = R_SCREENWIDTH-1;
			}
			// too far down
			if (next.second + bottomSide > R_SCREENHEIGHT) {
				if (!R_PHYSTYPE) ENTS[i].reverseAngle(false);
				else if (R_PHYSTYPE == 1) ENTS[i].Y = 1;
			}
			// too far up
			if (next.second < 0) {
				if (!R_PHYSTYPE) ENTS[i].reverseAngle(false);
				else if (R_PHYSTYPE == 1) ENTS[i].Y = R_SCREENHEIGHT-1;
			}

			ENTS[i].update(deltaTime);
			
			// update trails
			if (ENTS[i].useTrails) 
			{
				// remove old trails
				// update trail colors
				for (uint16_t S = 0; S < ENTS[i].trails.size(); ++S) {
					ENTS[i].trails[S].second.first --;
					if (ENTS[i].trails[S].second.first <= 0) {
						ENTS[i].trails.erase(ENTS[i].trails.begin() + S);
					}
					RGB_t COL;
					// if the lifetime exceeds the trailColor size use the last element
					if (ENTS[i].trails[S].second.first >= ENTS[i].trailColors.size())
						COL = ENTS[i].trailColors.back();
					
					else COL = ENTS[i].trailColors[ENTS[i].trails[S].second.first];
					
					ENTS[i].trails[S].second.second = COL;
					auto col_R = ENTS[i].trails[S].second.second.R;
					if ((col_R-(255-R_ENTBRIGHTNESS) >= 0))
						col_R -= (255-R_ENTBRIGHTNESS);
					else col_R = 0;

					auto col_G = ENTS[i].trails[S].second.second.G;
					if ((col_G-(255-R_ENTBRIGHTNESS) >= 0))
						col_G -= (255-R_ENTBRIGHTNESS);
					else col_G = 0;

					auto col_B = ENTS[i].trails[S].second.second.B;
					if ((col_B-(255-R_ENTBRIGHTNESS) >= 0))
						col_B -= (255-R_ENTBRIGHTNESS);
					else col_B = 0;

					SDL_SetRenderDrawColor(
						R_RENDERER,
						col_R,
						col_B,
						col_G,
						255
					);

					// blit sprite for trail
					for (uint16_t y = 0; y < ENTS[i].sprite.size(); ++y)
					{
						for (uint16_t x = 0; x < ENTS[i].sprite[y].size(); ++x)
						{
							auto col_R = ENTS[i].trails[S].second.second.R;
							if ((col_R-(255-R_ENTBRIGHTNESS) >= 0))
								col_R -= (255-R_ENTBRIGHTNESS);
							else col_R = 0;

							auto col_G = ENTS[i].trails[S].second.second.G;
							if ((col_G-(255-R_ENTBRIGHTNESS) >= 0))
								col_G -= (255-R_ENTBRIGHTNESS);
							else col_G = 0;

							auto col_B = ENTS[i].trails[S].second.second.B;
							if ((col_B-(255-R_ENTBRIGHTNESS) >= 0))
								col_B -= (255-R_ENTBRIGHTNESS);
							else col_B = 0;

							SDL_SetRenderDrawColor(
								R_RENDERER,
								col_R,
								col_B,
								col_G,
								255
							);
							// draw the point
							SDL_RenderDrawPoint(
								R_RENDERER,
								ENTS[i].trails[S].first.first + x,
								ENTS[i].trails[S].first.second + y
							);
						}
					}
				}
				
				// add a new trail
				ENTS[i].trails.push_back(
					{
						{ENTS[i].X, ENTS[i].Y},
						{ENTS[i].trailLife,ENTS[i].trailColors[0]}
					}
				);
			}

			// blit pixels for ent sprite
			if (ENTS[i].useSprite) {
				for (uint16_t y = 0; y < ENTS[i].sprite.size(); ++y)
				{
					for (uint16_t x = 0; x < ENTS[i].sprite[y].size(); ++x) 
					{
						auto col_R = ENTS[i].color.R;
						if ((col_R-(255-R_ENTBRIGHTNESS) >= 0))
							col_R -= (255-R_ENTBRIGHTNESS);
						else col_R = 0;

						auto col_G = ENTS[i].color.G;
						if ((col_G-(255-R_ENTBRIGHTNESS) >= 0))
							col_G -= (255-R_ENTBRIGHTNESS);
						else col_G = 0;

						auto col_B = ENTS[i].color.B;
						if ((col_B-(255-R_ENTBRIGHTNESS) >= 0))
							col_B -= (255-R_ENTBRIGHTNESS);
						else col_B = 0;

						SDL_SetRenderDrawColor(
							R_RENDERER,
							col_R,
							col_B,
							col_G,
							255
						);
						SDL_RenderDrawPoint(
							R_RENDERER, 
							ENTS[i].X + x,
							ENTS[i].Y + y
						);					
					}
				}
			}
			else SDL_RenderDrawPoint(R_RENDERER, (uint16_t)ENTS[i].X, (uint16_t)ENTS[i].Y);
			
		}
		// present render
		SDL_RenderPresent(R_RENDERER);
		SDL_SetRenderDrawColor(R_RENDERER, R_BACKCOLOR.R, R_BACKCOLOR.G, R_BACKCOLOR.B, 255);

		if (!R_NOCLEAR) SDL_RenderClear(R_RENDERER);
		
		timeOld = timeNew;
	}
	
	// gives a fucking stupid "potentially uninitialized local pointer variable" error so just keep it out
	//SDL_DestroyRenderer(R_RENDERER);
	SDL_DestroyWindow(R_WINDOW);
	SDL_Quit();

	return 0;
}