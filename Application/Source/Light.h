#pragma once
#include "Vertex.h"
struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	//to do: add a constructor
};