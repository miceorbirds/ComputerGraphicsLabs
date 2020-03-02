#pragma once
#include "ModelClass.h"
class Ball :
	public ModelClass
{
public:
	Ball();
	Ball(float x, float y) : ModelClass(x, y) {}
	float getPositionX();
	float getPositionY();
};

