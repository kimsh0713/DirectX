#pragma once
#include "Scene.h"
class Ingame :
	public Scene
{
public:
	Ingame(int type);

	// Start Ui
	Texture* blind;
	Texture* Ui_gst_tank;
	Texture* Ui_gst_dive;
	// UI
	Texture* Ui_base;
	Texture* Ui_score;
	Texture* Ui_stage;
	Texture* Ui_precent;
	Button* Ui_pause;
	Texture* Ui_abled_life;
	Texture* Ui_unabled_life;
	Texture* Ui_time;
	Texture* Ui_timer_tank;
	Texture* Ui_timer_bar;

	// GameOver
	float box_size = 1.5;
	int box_alpha = 255;
	Window* game_over;
	Texture* gov_box;

	// OBJECT
	Obj* player;
	Obj* enemy[10];
	Obj* boss;

	// TIMER
	int timer;
	Timer* playtime;

	// GameStart Ui
	float gst_y = -100;
	float blind_y = 450;
	int alpha = 255;
	// Ui
	float Y = 60;

	// DIVE
	int dive_count = 0;
	bool dive_type = false;
	float dive_time = 0;

	int type;
	int enemy_count = 3;

	static bool GameStart;
	static bool GameOver;

	static int stage;

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

