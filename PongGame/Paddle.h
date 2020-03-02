#pragma once
#include "ModelClass.h"
class Paddle :
	public ModelClass
{
public:
	Paddle();
	Paddle(float side);
	Paddle(float x, float y) : ModelClass(x, y) {}
	void updatePositionByClick(float, float);
	void UpdatePositionByDirection();
};

