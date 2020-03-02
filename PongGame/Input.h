#pragma once

class Input
{
public:
	Input();
	Input(const Input& input);
	~Input();

	bool Initialize();

	void KeyDown(unsigned int key);;
	void KeyUp(unsigned int key);;

	bool IsKeyPressed(unsigned int key);;

private:
	bool m_keys[256]{};
};

