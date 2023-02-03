#ifndef ENT_HPP_CHECK
#define ENT_HPP_CHECK

#include <iostream>
#include <vector>
#include "lib.hpp"

class Ent {
public:
	float X;
	float Y;
	float angle;
	float velocity;
	RGB_t color;
	// 0 = no sprite
	// 1 = use set sprite
	// 2 = use file sprite
	uint8_t useSprite = 1;
	std::string spriteFile = "";
	std::vector<std::vector<char>> sprite {};
	std::vector<std::pair<char,RGB_t>> colorKey = 
	{
		{'R',{255,0  ,0  }},
		{'G',{0  ,255,0  }},
		{'B',{0  ,0  ,255}},
		{'W',{255,255,255}},
		{'b',{0  ,0  ,0  }},
		{'Y',{255,255,0  }},
		{'P',{255,0  ,255}},
	};
	// use trails?
	bool useTrails = R_USETRAILS;
	// holds the trails
	// { { {X,Y}, {LIFE,{R,G,B} }} , ... }
	std::vector<std::pair<std::pair<float, float>, std::pair<uint16_t,RGB_t>>> trails {};
	// how long trails should stay
	uint16_t trailLife = R_TRAILLIFE;
	// trail colors as lifetime goes on
	// last trail will be defaulted to if lifetime exceeds size
	std::vector<RGB_t> trailColors {color};
	
	Ent
	(
		const float& g_X,
		const float& g_Y,
		const float& g_angle,
		const float& velocity,
		const RGB_t& g_color
	) :
		X(g_X),
		Y(g_Y),
		angle(g_angle),
		velocity(velocity),
		color(g_color)
	{}
	
	// update X and Y based on velocity and angle
	void update(const float& deltaTime)
	{
		X += (velocity * cos(angle*DGR))*deltaTime;
		Y += (velocity * sin(angle*DGR))*deltaTime;
	}

	// provides coordinates for the next update
	std::pair<float,float> nextUpdate (const float& deltaTime)
	{
		float dX = X, dY = Y;
		dX += (velocity * cos(angle*DGR))*deltaTime;
		dY += (velocity * sin(angle*DGR))*deltaTime;
		return {dX,dY};

	}
	
	// reverse the angle
	// used when the entity hits a wall
	void reverseAngle (bool side = false)
	{
		if (side) {
			angle = 180 - angle;
		}
		else {
			angle = - angle;
		}
		angle = normalizeAngle(angle);
	}
};

float midX = R_SCREENWIDTH / 2, midY = R_SCREENHEIGHT / 2;
/*
	const float& g_X,
	const float& g_Y, 
	const float& g_angle,
	const float& velocity,
	const RGB_t& g_color
*/

std::vector<Ent> ENTS = {};

#endif