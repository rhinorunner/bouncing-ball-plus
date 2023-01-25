#ifndef LIB_HPP_CHECK
#define LIB_HPP_CHECK

#include <iostream>
#include <chrono>

typedef struct RGB_t {
	uint8_t R;
	uint8_t G;
	uint8_t B;
};



// screen width
static constexpr uint16_t R_SCREENWIDTH  = 1020;
// screen height
static constexpr uint16_t R_SCREENHEIGHT = 890;

// background color
static const RGB_t R_BACKCOLOR = {0,0,0};

// frame delay
static constexpr uint16_t R_FRAMEDELAY = 50;



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