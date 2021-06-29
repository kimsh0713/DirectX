#include "DXUT.h"
#include "Ingame.h"

extern int score;

int Ingame::stage = 1;
bool Ingame::GameStart = false;
bool Ingame::GameOver = false;
bool Ingame::GameClear = false;

Ingame::Ingame(int type)
	:type(type)
{
}

void Ingame::Init()
{
	// 마우스 추가
	OBJ->Add(new Mouse, "Mouse");
	during = TIME->Create(0.01);
	during->Start();
	switch (type)
	{
	case 1:
		IMG->ReLoad("BG1");
		Ingame::stage = 1;
		Player::coloring_per = 0;
		OBJ->Add(new Enemy(7), "Boss")->pos = CENTER;
		OBJ->Add(new Enemy(1), "Enemy1")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
		OBJ->Add(new Enemy(2), "Enemy2")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
		enemy_count = 2;
		score = 0;
		GameOver = false;
		break;
	case 2:
		IMG->ReLoad("BG3");
		Ingame::stage = 2;
		Player::coloring_per = 0;
		OBJ->Add(new Enemy(8), "Boss")->pos = CENTER;
		OBJ->Add(new Enemy(3), "Enemy1")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
		OBJ->Add(new Enemy(4), "Enemy2")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
		OBJ->Add(new Enemy(5), "Enemy3")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
		enemy_count = 3;
		GameOver = false;
		break;
	case 3:
		IMG->ReLoad("BG5");
		Ingame::stage = 3;
		Player::coloring_per = 0;
		OBJ->Add(new Enemy(12), "Boss")->pos = CENTER;
		enemy_count = 0;
		GameOver = false;
		break;
	}
	// 플레이어 추가 / 플레이어 찾기
	OBJ->Add(new Player, "player")->pos = { 800,WINY };;
	player = OBJ->Find("player");

	Ui_gst_tank = IMG->Add("gst_tank");
	Ui_gst_dive = IMG->Add("gst_dive");
	blind = IMG->Add("blind");
	Ui_base = IMG->Add("ui_ingame_base");
	Ui_pause = new Button(IMG->Add("ui_ingame_pause button"), IMG->Add("ui_ingame_pause button_muscur"), { 80 , Y - 10 }, "", 60, 60, 0.2, [&]()->void {SCENE->Set("title"); });
	Ui_score = IMG->Add("ui_ingame_score");
	Ui_stage = IMG->Add("ui_ingame_stage");
	Ui_precent = IMG->Add("ui_ingame_%");
	Ui_abled_life = IMG->Add("ui_ingame_life");
	Ui_unabled_life = IMG->Add("ui_ingame_life2");
	Ui_time = IMG->Add("ui_ingame_time");
	Ui_timer_tank = IMG->Add("ui_ingame_time tank");
	Ui_timer_bar = IMG->Add("ui_ingame_time bar");
	// GAME OVER
	game_over = IMG->Add("blind");
	gov_box = IMG->Add("gov_box");
	gov_game = IMG->Add("gov_game");
	gov_over = IMG->Add("gov_over");
	gov_ink1 = IMG->Add("gov_ink1");
	gov_ink2 = IMG->Add("gov_ink2");
	score_box = IMG->Add("score_box");
	sc_txt = IMG->Add("ui_ingame_score");

	// GAMECLEAR
	gcl_box = IMG->Add("gcl_box");
	gcl_stage = IMG->Add("gcl_stage");
	gcl_clear = IMG->Add("gcl_clear");
	gcl_light = IMG->Add("gcl_light");

	OBJ->Add(new Mouse, "Mouse");

	timer = 60;
	playtime = TIME->Create(timer);

	boss = OBJ->Find("Boss");
	enemy[0] = OBJ->Find("Enemy1");
	enemy[1] = OBJ->Find("Enemy2");
	enemy[2] = OBJ->Find("Enemy3");

	zero = IMG->Add("0");
	one = IMG->Add("1");
	two = IMG->Add("2");
	three = IMG->Add("3");
	four = IMG->Add("4");
	five = IMG->Add("5");
	six = IMG->Add("6");
	seven = IMG->Add("7");
	eight = IMG->Add("8");
	nine = IMG->Add("9");
	comma = IMG->Add("comma");

	playtime->flag = true;
	// OVER_BUTTON
	gov_agbtn = new Button(IMG->Add("gov_agbtn"),IMG->Add("gov_agbtn cson"), { WINX / 2 - 280, WINY / 2 + 280 }, "", 348, 176, 0.18, [&]()->void { Player::bg_alpha = 255; gov_agbtn->Off();  if (type == 1) { SCENE->Set("stage1"); } else if (type == 2) { SCENE->Set("stage2"); } else if (type == 3) { SCENE->Set("stage3"); }player->hp = 3; GameOver = false; GameClear = false; Reset(); });
	gov_backbtn = new Button(IMG->Add("gov_backbtn"),IMG->Add("gcl_backbtn_cson"), { WINX / 2 + 280, WINY / 2 + 280 }, "", 348, 176, 0.18, [&]()->void { Player::bg_alpha = 255; gov_backbtn->Off(); GameOver = false; GameClear = false;  SCENE->Set("title"); Reset(); });
	gov_agbtn->Off();
	gov_backbtn->Off();

	// CLEAR_BUTTON
	gcl_nextbtn = new Button(IMG->Add("gcl_nextbtn"), IMG->Add("gcl_nextbtn_cson"), { WINX / 2 - 280, WINY / 2 + 280 }, "", 348, 176, 0.18, [&]()->void { Player::bg_alpha = 255; gcl_nextbtn->Off(); if (type == 1) { SCENE->Set("stage2"); } else if (type == 2) { SCENE->Set("stage3"); } else if (type == 3) {}player->hp = 3; GameClear = false; GameOver = false; Reset(); });
	gcl_backbtn = new Button(IMG->Add("gcl_backbtn"), IMG->Add("gcl_backbtn_cson"), { WINX / 2 + 280, WINY / 2 + 280 }, "", 348, 176, 0.18, [&]()->void { Player::bg_alpha = 255; gcl_backbtn->Off(); GameClear = false; GameOver = false; SCENE->Set("title"); Reset(); });
	gcl_nextbtn->Off();
	gcl_backbtn->Off();
}

void Ingame::Update()
{
	per = Player::coloring_per * 10;
	if (during->IsStop())
		render = true;

	if (player->hp <= 0)
	{
		GameOver = true;
		boss->flag = true;
		for (int i = 0; i < enemy_count; i++)
			enemy[i]->flag = true;
	}

	if (INPUT->Down('S'))
	{
		Ingame::GameStart = true;
		playtime->Start();
	}

	// M 누르면 마우스 추가
	if (INPUT->Down('M'))
	{
		OBJ->Add(new Mouse, "Mouse");
	}

	// 플레이어가 y130자표 이상 올라가면 Ui 올라감.	Player.y < 200
	if (player->pos.y <= 130)
	{
		if (Y > -30)
		{
			Y -= 4;
			sc_Y -= 4;
			Ui_pause->pos.y -= 4;
		}
	}
	else
	{
		if (Y < 60)
		{
			Y += 4;
			sc_Y += 4;
			Ui_pause->pos.y += 4;
		}
	}

	// 게임 클리어 퍼센트
	if (per >= 80)
	{
		GameClear = true;
		boss->flag = true;
		for (int i = 0; i < enemy_count; i++)
			enemy[i]->flag = true;
		playtime->flag = false;
		//switch (type)
		//{
		//case 1:
		//	stage = 2;
		//	SCENE->Set("stage2");
		//	break;
		//case 2:
		//	SCENE->Set("stage3");
		//	break;
		//case 3:
		//	SCENE->Set("clear");
		//	break;
		//}
	}

	// DIVE
	if (!Ingame::GameStart)
	{
		if (gst_y < WINY / 2 + 20)
		{
			gst_y += 7;
		}
		else
		{
			dive_time += DT;
		}
	}
	if (dive_count < 2)
	{
		if (dive_time < 0.3)
		{
			dive_type = true;
		}
		else
		{
			dive_type = false;
			if (dive_time > 0.6)
			{
				dive_count++;
				dive_time = 0;
			}
		}
	}
	else if (dive_count >= 2)
	{
		dive_type = true;
		if (dive_time > 0.5)
		{
			blind_y -= 12;
			alpha -= 3;
			if (alpha <= 0)
				alpha = 0;
			if (blind_y <= -850)
			{
				playtime->Start();
				Ingame::GameStart = true;
			}
		}
	}

	// GAME OVER
	if (Ingame::GameOver)
	{
		Player::bg_alpha = 0;
		if (box_size >= 1)
		{
			box_size -= 0.02;
			if (box_alpha <= 245)
				box_alpha += 10;
		}
		else
		{
			box_alpha = 255;
			shake_time += DT;
			if (shake)
			{
				switch (shake_count)
				{
				case 1:
					if (box_x < 825)
						box_x += 10;
					else
						shake_count++;
					break;
				case 2:
					if (box_x > 775)
						box_x -= 10;
					else
						shake_count++;
					break;
				case 3:
					if (box_x < 815)
						box_x += 10;
					else
						shake_count++;
					break;
				case 4:
					if (box_x > 785)
						box_x -= 10;
					else
						shake_count++;
					break;
				default:
					if (shake_time > 0.6)
					{
						shake = false;
						if (box_x > 795)
							box_x += 5;
					}
					break;
				}
			}
			else
				switch (over_count)
				{
				case 1:
					if (game_x <= 470)
						game_x += 15;
					else over_count++;
					break;
				case 2:
					if (over_alpha <= 245)
						over_alpha += 10;
					else over_count++;
					break;
				case 3:
					if (ink1_alpha <= 235)
						ink1_alpha += 20;
					else over_count++;
					break;
				case 4:
					if (ink2_alpha <= 235)
						ink2_alpha += 20;
					else over_count++;
					break;
				case 5:
					if (sc_box_alpha <= 230)
						sc_box_alpha += 25;
					else over_count++;
					break;
				case 6:
					sc_txt_render = true;
					over_count++;
					break;
				case 7:
					score_render = true;
					over_count++;
					break;
				case 8:
					if (score_alpha <= 240)
						score_alpha += 15;
					else
						over_count++;
					break;
				case 9:
					if (score_alpha >= 15)
						score_alpha -= 15;
					else
						over_count++;
					break;
				case 10:
					if (score_alpha <= 240)
						score_alpha += 15;
					else
						over_count++;
					break;
				case 11:
					gov_agbtn->On();
					gov_backbtn->On();
					break;
				}
		}
	}

	// GAME CLEAR
	if (Ingame::GameClear)
	{
		Player::bg_alpha = 0;
		switch (clear_count)
		{
		case 1:
			if (box_size >= 1)
			{
				box_size -= 0.02;
				if (box_alpha <= 245)
					box_alpha += 10;
			}
			else clear_count++;
			break;
		case 2:
			box_alpha = 255;
			shake_time += DT;
			if (box_x < 825)
				box_x += 10;
			else
				clear_count++;
			break;
		case 3:
			if (box_x > 775)
				box_x -= 10;
			else
				clear_count++;
			break;
		case 4:
			if (box_x < 815)
				box_x += 10;
			else
				clear_count++;
			break;
		case 5:
			if (box_x > 785)
				box_x -= 10;
			else
				clear_count++;
			break;
		case 6:
			if (shake_time > 0.6)
			{
				shake = false;
				if (box_x > 795)
					box_x += 5;
			}
			else clear_count++;
			break;
		case 7:
			if (stage_x <= 425)
				stage_x += 15;
			else clear_count++;
			break;
		case 8:
			if (clear_alpha <= 245)
				clear_alpha += 10;
			else clear_count++;
			break;
		case 9:
			if (sc_box_alpha <= 230)
				sc_box_alpha += 25;
			if (light_alpha <= 247)
				light_alpha += 8;
			else
			{
				clear_count++;
				render_count++;
			}
			break;
		case 10:
			if (light_alpha >= 8)
				light_alpha -= 8;
			else clear_count++;
			break;
		case 11:
			if (light_alpha <= 247)
				light_alpha += 8;
			else clear_count++;
			break;
		}
	}
	switch (render_count)
	{
	case 1:
		score_render = true;
		sc_txt_render = true;
		render_count++;
		break;
	case 2:
		if (score_alpha <= 235)
			score_alpha += 20;
		else render_count++;
		break;
	case 3:
		if (score_alpha >= 20)
			score_alpha -= 20;
		else render_count++;
		break;
	case 4:
		if (score_alpha <= 235)
			score_alpha += 20;
		else render_count++;
		break;
	case 5:
		gcl_nextbtn->On();
		gcl_backbtn->On();
		break;
	}


	if (Ingame::GameOver || Ingame::GameClear)
		playtime->flag = false;
}

void Ingame::Render()
{
	// GAMESTART
	if (!Ingame::GameStart)
	{
		blind->Render({ WINX / 2, blind_y }, RT_ZERO, { 1,1 }, 0, 0.15);
		Ui_gst_tank->Render({ WINX / 2, gst_y }, RT_ZERO, { 1,1 }, 0, 0.09, D3DCOLOR_RGBA(255, 255, 255, alpha));

		if (gst_y >= WINY / 2 + 20)
		{
			if (dive_type)
				Ui_gst_dive->Render({ WINX / 2, gst_y + 100 }, RT_ZERO, { 1,1 }, 0, 0.08, D3DCOLOR_RGBA(255, 255, 255, alpha));
		}
	}

	// GAMEOVER
	if (Ingame::GameOver)
	{
		game_over->Render(CENTER, RT_ZERO, { 1,1 }, 0, 0.19);
		gov_box->Render({ box_x, WINY / 2 - 100 }, RT_ZERO, { box_size, box_size }, 0, 0.14, D3DCOLOR_RGBA(255, 255, 255, box_alpha));
		gov_game->Render({ game_x, WINY / 2 - 20 }, RT_ZERO, { 1,1 }, 0, 0.139);
		gov_over->Render({ WINX / 2 + 310, WINY / 2 - 20 }, RT_ZERO, { 1,1 }, 0, 0.139, D3DCOLOR_RGBA(255, 255, 255, over_alpha));
		gov_ink1->Render({ WINX / 2 + 230, WINY / 2 - 190 }, RT_ZERO, { 1,1 }, 0, 0.141, D3DCOLOR_RGBA(255, 255, 255, ink1_alpha));
		gov_ink2->Render({ WINX / 2 - 300, WINY / 2 - 110 }, RT_ZERO, { 1,1 }, 0, 0.141, D3DCOLOR_RGBA(255, 255, 255, ink2_alpha));
		score_box->Render({ box_x, WINY / 2 + 120 }, RT_ZERO, { 1,1 }, 0, 0.138, D3DCOLOR_RGBA(255, 255, 255, sc_box_alpha));
		if (sc_txt_render)
		{
			sc_txt->Render({ WINX / 2 - 180, WINY / 2 + 120 }, RT_ZERO, { 1.5,1.5 }, 0, 0.137);
		}
		if (score_render)
		{
			// 일의 자리
			TextureNum(Nums(Player::Score, 0))->Render({ WINX / 2 + 250, WINY / 2 + 120 }, RT_ZERO, { 1.4,1.4 }, 0, 0.137, D3DCOLOR_RGBA(255, 255, 255, score_alpha));
			TextureNum(Nums(Player::Score, 1))->Render({ WINX / 2 + 198, WINY / 2 + 120 }, RT_ZERO, { 1.4,1.4 }, 0, 0.137, D3DCOLOR_RGBA(255, 255, 255, score_alpha));
			TextureNum(Nums(Player::Score, 2))->Render({ WINX / 2 + 146, WINY / 2 + 120 }, RT_ZERO, { 1.4,1.4 }, 0, 0.137, D3DCOLOR_RGBA(255, 255, 255, score_alpha));
			TextureNum(Nums(Player::Score, 3))->Render({ WINX / 2 + 94, WINY / 2 + 120 }, RT_ZERO, { 1.4,1.4 }, 0, 0.137, D3DCOLOR_RGBA(255, 255, 255, score_alpha));
			TextureNum(Nums(Player::Score, 4))->Render({ WINX / 2 + 42, WINY / 2 + 120 }, RT_ZERO, { 1.4,1.4 }, 0, 0.137, D3DCOLOR_RGBA(255, 255, 255, score_alpha));
			TextureNum(Nums(Player::Score, 5))->Render({ WINX / 2 - 10, WINY / 2 + 120 }, RT_ZERO, { 1.4,1.4 }, 0, 0.137, D3DCOLOR_RGBA(255, 255, 255, score_alpha));
		}
	}

	// GAMECLEAR
	if (Ingame::GameClear)
	{
		game_over->Render(CENTER, RT_ZERO, { 1,1 }, 0, 0.19);
		gcl_box->Render({ box_x, WINY / 2 - 50 }, RT_ZERO, { box_size, box_size }, 0, 0.14, D3DCOLOR_RGBA(255, 255, 255, box_alpha));
		gcl_stage->Render({ stage_x, WINY / 2 + 10 }, RT_ZERO, { 1,1 }, 0, 0.139);
		gcl_clear->Render({ WINX / 2 + 345, WINY / 2 + 10 }, RT_ZERO, { 1,1 }, 0, 0.139, D3DCOLOR_RGBA(255, 255, 255, clear_alpha));
		gcl_light->Render({ 800, WINY / 2 - 165 }, RT_ZERO, { 1,1 }, 0, 0.141, D3DCOLOR_RGBA(255, 255, 255, light_alpha));
		score_box->Render({ box_x, WINY / 2 + 145 }, RT_ZERO, { 1,1 }, 0, 0.138, D3DCOLOR_RGBA(255, 255, 255, sc_box_alpha));

		if (sc_txt_render)
		{
			sc_txt->Render({ WINX / 2 - 180, WINY / 2 + 145 }, RT_ZERO, { 1.5,1.5 }, 0, 0.137);
		}
		if (score_render)
		{
			// 일의 자리
			TextureNum(Nums(Player::Score, 0))->Render({ WINX / 2 + 250, WINY / 2 + 145 }, RT_ZERO, { 1.5,1.5 }, 0, 0.137, D3DCOLOR_RGBA(255, 255, 255, score_alpha));
			TextureNum(Nums(Player::Score, 1))->Render({ WINX / 2 + 198, WINY / 2 + 145 }, RT_ZERO, { 1.5,1.5 }, 0, 0.137, D3DCOLOR_RGBA(255, 255, 255, score_alpha));
			TextureNum(Nums(Player::Score, 2))->Render({ WINX / 2 + 146, WINY / 2 + 145 }, RT_ZERO, { 1.5,1.5 }, 0, 0.137, D3DCOLOR_RGBA(255, 255, 255, score_alpha));
			TextureNum(Nums(Player::Score, 3))->Render({ WINX / 2 + 94, WINY / 2 + 145 }, RT_ZERO, { 1.5,1.5 }, 0, 0.137, D3DCOLOR_RGBA(255, 255, 255, score_alpha));
			TextureNum(Nums(Player::Score, 4))->Render({ WINX / 2 + 42, WINY / 2 + 145 }, RT_ZERO, { 1.5,1.5 }, 0, 0.137, D3DCOLOR_RGBA(255, 255, 255, score_alpha));
			TextureNum(Nums(Player::Score, 5))->Render({ WINX / 2 - 10, WINY / 2 + 145 }, RT_ZERO, { 1.5,1.5 }, 0, 0.137, D3DCOLOR_RGBA(255, 255, 255, score_alpha));
		}
	}

	// SCORE
	TextureNum(Nums(Player::Score, 0))->Render({ sc_X0, sc_Y+5 }, RT_ZERO, { 0.7,0.7 }, 0, 0.2);
	TextureNum(Nums(Player::Score, 1))->Render({ sc_X1, sc_Y+5 }, RT_ZERO, { 0.7,0.7 }, 0, 0.2);
	TextureNum(Nums(Player::Score, 2))->Render({ sc_X2, sc_Y+5 }, RT_ZERO, { 0.7,0.7 }, 0, 0.2);
	TextureNum(Nums(Player::Score, 3))->Render({ sc_X3, sc_Y+5 }, RT_ZERO, { 0.7,0.7 }, 0, 0.2);
	TextureNum(Nums(Player::Score, 4))->Render({ sc_X4, sc_Y+5 }, RT_ZERO, { 0.7,0.7 }, 0, 0.2);
	TextureNum(Nums(Player::Score, 5))->Render({ sc_X5, sc_Y+5 }, RT_ZERO, { 0.7,0.7 }, 0, 0.2);

	// 스테이지
	TextureNum(Nums(Ingame::stage, 0))->Render({ 665, sc_Y }, RT_ZERO, { 1,1 }, 0, 0.2);

	// 점령도
	TextureNum(Nums((int)per, 0))->Render({ 800, sc_Y }, RT_ZERO, { 0.9,0.9 }, 0, 0.2);
	TextureNum(Nums((int)per, 1))->Render({ 752, sc_Y }, RT_ZERO, { 0.9,0.9 }, 0, 0.2);
	switch (Nums((int)per, 2))
	{
	case 1:
		one->Render({ 718, sc_Y }, RT_ZERO, { 0.9,0.9 }, 0, 0.2);
		break;
	case 2:
		two->Render({ 718, sc_Y }, RT_ZERO, { 0.9,0.9 }, 0, 0.2);
		break;
	case 3:
		three->Render({ 718, sc_Y }, RT_ZERO, { 0.9,0.9 }, 0, 0.2);
		break;
	case 4:
		four->Render({ 718, sc_Y }, RT_ZERO, { 0.9,0.9 }, 0, 0.2);
		break;
	case 5:
		five->Render({ 718, sc_Y }, RT_ZERO, { 0.9,0.9 }, 0, 0.2);
		break;
	case 6:
		six->Render({ 718, sc_Y }, RT_ZERO, { 0.9,0.9 }, 0, 0.2);
		break;
	case 7:
		seven->Render({ 718, sc_Y }, RT_ZERO, { 0.9,0.9 }, 0, 0.2);
		break;
	case 8:
		eight->Render({ 718, sc_Y }, RT_ZERO, { 0.9,0.9 }, 0, 0.2);
		break;
	case 9:
		nine->Render({ 718, sc_Y }, RT_ZERO, { 0.9,0.9 }, 0, 0.2);
		break;
	}

	comma->Render({ 776, sc_Y + 8 }, RT_ZERO, { 0.9,0.9 }, 0, 0.2);

	Ui_base->Render({ WINX / 2, Y }, RT_ZERO, { 1,1 }, 0, 0.3);
	Ui_score->Render({ 200, (sc_Y) }, RT_ZERO, { 1,1 }, 0, 0.3);
	Ui_stage->Render({ 545,(sc_Y) }, RT_ZERO, { 1,1 }, 0, 0.3);
	Ui_precent->Render({ WINX / 2 + 35, (sc_Y) }, RT_ZERO, { 1,1 }, 0, 0.3);

	if (render)
	{
		switch (player->hp)
		{
		case 1:
			Ui_unabled_life->Render({ WINX / 2 + 250, (sc_Y) }, RT_ZERO, { 1,1 }, 0, 0.3);
			Ui_unabled_life->Render({ WINX / 2 + 180, (sc_Y) }, RT_ZERO, { 1,1 }, 0, 0.3);
			Ui_abled_life->Render({ WINX / 2 + 110, (sc_Y) }, RT_ZERO, { 1,1 }, 0, 0.3);
			break;
		case 2:
			Ui_unabled_life->Render({ WINX / 2 + 250, (sc_Y) }, RT_ZERO, { 1,1 }, 0, 0.3);
			Ui_abled_life->Render({ WINX / 2 + 180, (sc_Y) }, RT_ZERO, { 1,1 }, 0, 0.3);
			Ui_abled_life->Render({ WINX / 2 + 110, (sc_Y) }, RT_ZERO, { 1,1 }, 0, 0.3);
			break;
		case 3:
			Ui_abled_life->Render({ WINX / 2 + 250, (sc_Y) }, RT_ZERO, { 1,1 }, 0, 0.3);
			Ui_abled_life->Render({ WINX / 2 + 180, (sc_Y) }, RT_ZERO, { 1,1 }, 0, 0.3);
			Ui_abled_life->Render({ WINX / 2 + 110, (sc_Y) }, RT_ZERO, { 1,1 }, 0, 0.3);
			break;
		default:
			Ui_abled_life->Render({ WINX / 2 + 250, (sc_Y) }, RT_ZERO, { 1,1 }, 0, 0.3);
			Ui_abled_life->Render({ WINX / 2 + 180, (sc_Y) }, RT_ZERO, { 1,1 }, 0, 0.3);
			Ui_abled_life->Render({ WINX / 2 + 110, (sc_Y) }, RT_ZERO, { 1,1 }, 0, 0.3);
			break;
		}
	}

	Ui_time->Render({ WINX / 2 + 360, (sc_Y) }, RT_ZERO, { 1,1 }, 0, 0.3);
	Ui_timer_tank->Render({ WINX / 2 + 600, (sc_Y) }, RT_ZERO, { 1,1 }, 0, 0.3);
	RECT hprt =
	{
		0,
		0,
		Ui_timer_bar->info.Width / playtime->set * playtime->cur,
		Ui_timer_bar->info.Height
	};
	Ui_timer_bar->Render({ WINX / 2 + 605, (sc_Y) }, hprt, { 1,1 }, 0, 0.29);

}

void Ingame::Release()
{

}


void Ingame::Reset()
{
	playtime->flag = true;
	shake_time = 0;
	shake = true;
	clear_count = 1;
	shake_count = 1;
	over_count = 1;
	render_count = 0;
	game_x = -300;
	stage_x = -500;
	box_size = 1.5;
	box_x = 800;
	box_alpha = 0;
	over_alpha = 0;
	clear_alpha = 0;
	light_alpha = 0;
	ink1_alpha = 0;
	ink2_alpha = 0;
	sc_box_alpha = 0;
	score_alpha = 0;
	sc_txt_render = false;
	score_render = false;
}

int Ingame::Nums(int num, int index) //num에 스코어를 넣고, index 0 = 1의자리 index 1 = 2의 자리
{
	vector<int> nums;

	while (num != 0)
	{
		nums.emplace_back(num % 10);
		num /= 10;
	}

	return nums.size() <= index ? 0 : nums[index];
}

Texture* Ingame::TextureNum(int num)
{
	Texture* result = nullptr;

	switch (num)
	{
	case 0:
		result = IMG->Add("0");
		break;
	case 1:
		result = IMG->Add("1");
		break;
	case 2:
		result = IMG->Add("2");
		break;
	case 3:
		result = IMG->Add("3");
		break;
	case 4:
		result = IMG->Add("4");
		break;
	case 5:
		result = IMG->Add("5");
		break;
	case 6:
		result = IMG->Add("6");
		break;
	case 7:
		result = IMG->Add("7");
		break;
	case 8:
		result = IMG->Add("8");
		break;
	case 9:
		result = IMG->Add("9");
		break;
	}

	return result;
}