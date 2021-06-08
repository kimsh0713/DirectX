#pragma once
class ScrollMap
{
public:
	ScrollMap(Texture* bg)
		:bg(bg), scroll(0) {}

	~ScrollMap() { ; };

	void Update(float speed);
	void Render();

	Texture* bg;
	float scroll;
};

