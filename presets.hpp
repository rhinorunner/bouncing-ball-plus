/***********

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
((rand.genRand() % 4)),
{
	(uint8_t)((rand.genRand() % 70)+186),
	(uint8_t)((rand.genRand() % 70)+186),
	(uint8_t)((rand.genRand() % 70)+186)
}

random colors, large starburst

(R_SCREENWIDTH/2),
(R_SCREENHEIGHT/2),
((rand.genRand() % 360)),
((rand.genRand() % 4)),
{
	(uint8_t)((rand.genRand() % 256)),
	(uint8_t)((rand.genRand() % 256)),
	(uint8_t)((rand.genRand() % 256))
}

yellow with some green and red, reaching accross the screen

(0),
((rand.genRand() % R_SCREENHEIGHT)),
((rand.genRand() % 360)),
((rand.genRand() % 4)),
{
	(uint8_t)((rand.genRand() % 175)+130),
	(uint8_t)((rand.genRand() % 175)+130),
	(uint8_t)((rand.genRand() % 20))
}
***********/