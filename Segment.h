#pragma once
#include "olcPixelGameEngine.h"


#include <math.h>

class Segment
{
public:
	float len;
	float angle;
	olc::vi2d a;
	Segment* parent = nullptr;
public:
	Segment(olc::vi2d, float, float);
	Segment(Segment* , float, float);
	olc::vi2d b();

	void Update(olc::vi2d);
	void LookAt(olc::vi2d);
	void MoveTo(olc::vi2d);
	void MoveA(olc::vi2d);
	void Draw(olc::PixelGameEngine*);
};

