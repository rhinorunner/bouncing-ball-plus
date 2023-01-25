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
	std::vector<Trail_t> trails;
	
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
Ent entR{midX,midY,74,1,{255,0,0}};
Ent entG{midX,midY,303,2,{0,255,0}};
Ent entB{midX,midY,23,.4,{0,0,255}};
Ent entW{midX,midY,234.23,2.4999,{255,255,255}};
Ent entY{midX,midY,12,1.5,{255,255,0}};
Ent entO{midX,midY,90.24,.82,{255,165,0}};
Ent entP{midX,midY,29.948,1.287,{255,0,255}};

std::vector<Ent> ENTS = {entR,entG,entB,entW,entY,entO,entP};

#endif