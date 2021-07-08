#pragma once
class Effect
{
public:
	Effect(Texture* fx, V2 pos, int rot, int flag);
	void Render();

	Texture* fx;
	V2 size, pos;

	float timer = 0;

	int flag = 0, rot, alpha;
};

