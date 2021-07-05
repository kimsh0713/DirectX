#pragma once
#include "Scene.h"
class Ingame :
	public Scene
{
public:
	Ingame(int type);

	// Start Ui
	Texture* blind;
	Texture* dive_blind;
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
	int over_count = 1;
	float game_x = -300;
	float box_x = 800;
	float box_size = 1.5;
	int box_alpha = 0;
	int over_alpha = 0;
	int ink1_alpha = 0;
	int ink2_alpha = 0;
	int sc_box_alpha = 0;
	int score_alpha = 0;
	bool sc_txt_render = false;
	bool score_render = false;
	Texture* game_over;
	Texture* gov_box;
	Texture* gov_game;
	Texture* gov_over;
	Texture* gov_ink1;
	Texture* gov_ink2;
	Texture* score_box;
	Texture* sc_txt;
	Button* gov_agbtn;
	Button* gov_backbtn;
	// BOX shake
	int shake_count = 1;
	bool shake = true;
	float shake_time = 0;

	// GameClear
	int clear_count = 1;
	int render_count = 0;
	float stage_x = -500;
	int cl_box_alpha = 0;
	int clear_alpha = 0;
	int light_alpha = 0;
	Texture* gcl_box;
	Texture* gcl_stage;
	Texture* gcl_clear;
	Texture* gcl_light;
	Button* gcl_nextbtn;
	Button* gcl_backbtn;

	// PAUSE
	Window* win_pause;

	// OBJECT
	Obj* player;
	Obj* enemy[10];
	Obj* boss;

	// TIMER
	int timer;
	Timer* playtime;
	Timer* during;

	// GameStart Ui
	float gst_y = -100;
	float blind_y = 450;
	int alpha = 255;
	// Ui
	float Y = 60;
	float sc_Y = 50;
	float sc_X0 = 425;
	float sc_X1 = 399.8;
	float sc_X2 = 374.6;
	float sc_X3 = 349.4;
	float sc_X4 = 324.2;
	float sc_X5 = 299;

	// DIVE
	int dive_count = 0;
	bool dive_type = false;
	float dive_time = 0;

	// PAUSE
	Button* continue_button;
	Button* main_button;
	Button* sound_button;
	Button* music_button;
	Texture* Ing_sound_on;
	Texture* Ing_sound_mute;
	Texture* Ing_music_on;
	Texture* Ing_music_mute;

	// Number
	Texture * zero;
	Texture * one;
	Texture * two;
	Texture * three;
	Texture * four;
	Texture * five;
	Texture * six;
	Texture * seven;
	Texture * eight;
	Texture * nine;
	Texture * comma;

	bool isSound = true;

	float per;
	bool start = false;

	int type;
	int enemy_count = 3;
	bool render = false;

	Obj* shark;

	static bool GameStart;
	static bool GameOver;
	static bool GameClear;
	static bool GamePause;

	static int stage;

	Sound* Back_Ground_music;

	void Reset();
	int Nums(int num, int index);
	Texture* TextureNum(int num);

	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

