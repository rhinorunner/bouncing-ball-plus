#ifndef LIB_HPP_CHECK
#define LIB_HPP_CHECK

#include <iostream>
#include <chrono>

#pragma pack(1)

typedef struct RGB_t {
	uint8_t R;
	uint8_t G;
	uint8_t B;
};

/*

[NUM][ / ][ * ][ - ]
[ 7 ][ 8 ][ 9 ][ + ]
[ 4 ][ 5 ][ 6 ][ + ]
[ 1 ][ 2 ][ 3 ][ENT]
[ 0 ][ 0 ][ . ][ENT]


[ + ] = up brightness
[ - ] = down brightness

[ * ] = set all ents to middle
[ / ] = set all ents to random
[ 9 ] = sey all ent angles to random

[ 0 ] = clear screen

[ . ] = pause/unpause

*/

/// GRAPHICS STUFF

// screen width
static constexpr uint16_t R_SCREENWIDTH  = 1920;
// screen height
static constexpr uint16_t R_SCREENHEIGHT = 1080;
// background color
static const RGB_t R_BACKCOLOR = {0,0,0};
// if true, dont clear the screen after each frame
static constexpr bool R_NOCLEAR = false;
// use trails?
static constexpr bool R_USETRAILS = true;
// default trail length
static constexpr uint16_t R_TRAILLIFE = 100;

/// FRAME STUFF

// delta time calibration
static constexpr float time_calib = .05;
// use frame delays?
static constexpr bool R_USEFRAMEDELAY = true;
// frame delay
static constexpr uint16_t R_FRAMEDELAY = 0;
// delta time replacement
static constexpr float R_DELTAREPLACE = .5;

/// PHYSICS STUFF

// 0 = bounce off walls
// 1 = warp around screen
static constexpr uint8_t R_PHYSTYPE = 0;

/// OTHER

// path because i am stupid
static const std::string STR_PATH = "C:/Users/cubez/source/repos/RAYCASTING/RAYCASTING/";

// ent brightness value
static uint8_t R_ENTBRIGHTNESS = 255;
// ent brightness change step value
static constexpr uint8_t R_BRTSTEP = 5;


typedef struct Trail_t {
	float X;
	float Y;
	std::vector<RGB_t> trail;
	uint16_t trailIndex;
};

static constexpr double pi  = 3.1415926535;
static const     double DGR = pi / 180;

float normalizeAngle(float angle) {
	while (angle < 0)    angle += 360;
	while (angle >= 360) angle -= 360;
	return angle;
}

class BetterRand {
public:
	// adds this to random each time, optional
	uint32_t extraRand;
	BetterRand(const uint32_t& ExtraRand = 20907) : extraRand(ExtraRand) {};
	uint32_t genRand(const uint8_t& extra = 4, bool resetExtraRand = true, uint8_t resetERextraIt = 2) 
	{
		if (resetExtraRand) extraRand = genRand(resetERextraIt,false);
		// set random to unix time
		auto cool = std::chrono::system_clock::now();
		auto very = 
			(unsigned int) 
			std::chrono::time_point_cast
			<std::chrono::milliseconds>
			(cool).time_since_epoch().count();
		// add random()
		if (extra >= 1) very -= rand();
		// add line number
		if (extra >= 2) very += __LINE__;
		// add an iteration (extra = 2)
		if (extra >= 3) very += genRand(2,false);
		// bitshift right or left based on another iteration
		if (extra >= 4) 
		(genRand(2,false)) % 2 ? very >>= 1 : very <<= 1;
		// subtract an iteration (extra = 4)
		if (extra >= 5) very -= genRand(4, false);
		return (very + extraRand);
	}
};

#endif