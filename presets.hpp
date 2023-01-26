/***********

classic random everything

((rand.genRand() % R_SCREENWIDTH)),
((rand.genRand() % R_SCREENWIDTH)),
((rand.genRand() % 360)),
((rand.genRand() % 150)/100)+5,
{
	(uint8_t)((rand.genRand() % 256)),
	(uint8_t)((rand.genRand() % 256)),
	(uint8_t)((rand.genRand() % 256))
}

random colors, diagonal squares

((rand.genRand() % 4) * (R_SCREENWIDTH / 4)),
((rand.genRand() % 4) * (R_SCREENHEIGHT / 4)),
((rand.genRand() % 4)*90+45),
((rand.genRand() % 150) / 10) + 1,
{
	(uint8_t)((rand.genRand() % 256)),
	(uint8_t)((rand.genRand() % 256)),
	(uint8_t)((rand.genRand() % 256))
}

about green, split vertical lines

((rand.genRand() % 16) * (R_SCREENWIDTH / 16)),
((rand.genRand() % 16) * (R_SCREENHEIGHT / 16)),
((rand.genRand() % 2)*180)+89.9,
((rand.genRand() % 100) / 10) + 5,
{
	(uint8_t)((rand.genRand() % 50)),
	(uint8_t)((rand.genRand() % 100)+156),
	(uint8_t)((rand.genRand() % 50))
}

magenta, rhombi

((rand.genRand() % 200) * (R_SCREENWIDTH / 200)),
((rand.genRand() % 4) * (R_SCREENHEIGHT / 4)),
((rand.genRand() % 8)*45),
((rand.genRand() % 100) / 10) + 5,
{
	(uint8_t)((rand.genRand() % 150)+100),
	(uint8_t)((rand.genRand() % 50)),
	(uint8_t)((rand.genRand() % 150)+100)
}

whited colors, starbursts

((rand.genRand() % 4) * (R_SCREENWIDTH / 4)),
((rand.genRand() % 4) * (R_SCREENHEIGHT / 4)),
((rand.genRand() % 100)*(360/10)),
((rand.genRand() % 4)+.1),
{
	(uint8_t)((rand.genRand() % 70)+186),
	(uint8_t)((rand.genRand() % 70)+186),
	(uint8_t)((rand.genRand() % 70)+186)
}

random colors, large starburst

(R_SCREENWIDTH/2),
(R_SCREENHEIGHT/2),
((rand.genRand() % 360)),
((rand.genRand() % 4)+.1),
{
	(uint8_t)((rand.genRand() % 256)),
	(uint8_t)((rand.genRand() % 256)),
	(uint8_t)((rand.genRand() % 256))
}

yellow with some green and red, reaching accross the screen

(0),
((rand.genRand() % R_SCREENHEIGHT)),
((rand.genRand() % 360)),
((rand.genRand() % 4)+.1),
{
	(uint8_t)((rand.genRand() % 175)+130),
	(uint8_t)((rand.genRand() % 175)+130),
	(uint8_t)((rand.genRand() % 20))
}

green variants, growing upwards

((rand.genRand() % R_SCREENWIDTH)),
(R_SCREENHEIGHT),
((rand.genRand() % 360)),
((rand.genRand() % 3)+3),
{
	(uint8_t)((rand.genRand() % 34)+30),
	(uint8_t)((rand.genRand() % 100)+156),
	(uint8_t)((rand.genRand() % 90)+5)
}

red green and blue, random

((rand.genRand() % R_SCREENWIDTH)),
((rand.genRand() % R_SCREENWIDTH)),
((rand.genRand() % 360)),
((rand.genRand() % 150)/100)+5,
{
	(uint8_t)(i % 3 == 0 ? 255 : 0),
	(uint8_t)(i % 3 == 1 ? 255 : 0),
	(uint8_t)(i % 3 == 2 ? 255 : 0)
}

organic yellow, spread from top right

(0),
(0),
((rand.genRand() % 360)),
(2),
{
	(uint8_t)((rand.genRand() % 30)+220),
	(uint8_t)((rand.genRand() % 50)+200),
	(uint8_t)((rand.genRand() % 10)+90)
}

green and magenta, fast colliding sunbursts

(!(i % 2) ? 0 : R_SCREENWIDTH),
(!(i % 2) ? 0 : R_SCREENHEIGHT),
(!(i % 2) ? (rand.genRand() % 45) : ((rand.genRand() % 45)+45)),
20,
{
	(uint8_t)(!(i % 2) ? 0 : 255),
	(uint8_t)(!(i % 2) ? 255 : 0),
	(uint8_t)(!(i % 2) ? 0 : 255)
}

black and white, random white with black cutting in

((rand.genRand() % R_SCREENWIDTH)),
((rand.genRand() % R_SCREENWIDTH)),
((rand.genRand() % 360)),
((rand.genRand() % 150)/100)+5,
{
	(uint8_t)(!(i % 10) ? 255 : 0),
	(uint8_t)(!(i % 10) ? 255 : 0),
	(uint8_t)(!(i % 10) ? 255 : 0)
}
***********/

/*
((rand.genRand() % R_SCREENWIDTH)),
((rand.genRand() % R_SCREENWIDTH)),
((rand.genRand() % 360)),
((rand.genRand() % 150)/100)+5,
{
	(uint8_t)((rand.genRand() % 256)),
	(uint8_t)((rand.genRand() % 256)),
	(uint8_t)((rand.genRand() % 256))
}
*/