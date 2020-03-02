#include "Paddle.h"

Paddle::Paddle()
{
	currentLocation[0] = 0;
	currentLocation[1] = -1;
	direction[0] = 0;
	direction[1] = 0;
	vertices[0] = { 0.02f, 0.15f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	vertices[1] = { 0.02f, -0.15, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	vertices[2] = { -0.02f, -0.15f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	vertices[3] = { -0.02f, 0.15f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f };
	for (auto i = 0; i < 4; i++) {
		vertices[i].x += -1;
	}
}


// PADDLE INIT!
Paddle::Paddle(float side)
{
	currentLocation[0] = side;
	currentLocation[1] = 0;
	direction[0] = 0;
	direction[1] = 0;
	vertices[0] = { 0.02f, 0.15f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
	vertices[1] = { 0.02f, -0.15, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
	vertices[2] = { -0.02f, -0.15f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
	vertices[3] = { -0.02f, 0.15f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f };
	for (auto i = 0; i < 4; i++) {
		vertices[i].x += side;
	}
}

void Paddle::updatePositionByClick(float x, float y)
{
	if (currentLocation[1] <= 0.85 && y > 0 || currentLocation[1] >= -0.85 && y < 0) {
		currentLocation[1] += y;
		for (auto i = 0; i < 4; i++) {
			vertices[i].y += y;
		}
	}
}

void Paddle::UpdatePositionByDirection()
{
}
