#pragma once
class MainGame
{
public:
	MainGame() { ; };
	~MainGame() { ; };

	void Init();
	void Update();
	void Render();
	void Release();
	void Lost();
	void Reset();
};

