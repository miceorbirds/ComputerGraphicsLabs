#include "Input.h"

Input::Input()
{
}

Input::Input(const Input& input)
{
}

Input::~Input()
{
}

bool Input::Initialize()
{
	for (bool& m_key : m_keys)
	{
		m_key = false;
	}

	return true;
}

void Input::KeyDown(unsigned int key)
{
	m_keys[key] = true;
}

void Input::KeyUp(unsigned int key)
{
	m_keys[key] = false;
}

bool Input::IsKeyPressed(unsigned int key)
{
	return m_keys[key];
}



