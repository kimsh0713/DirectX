#include "DXUT.h"
#include "Ingame.h"

extern int score;

int Ingame::stage = 1;
bool Ingame::GameStart = false;
bool Ingame::GameOver = false;

Ingame::Ingame(int type)
	:type(type)
{
}

void Ingame::Init()
{
	// 마우스 추가
	OBJ->Add(new Mouse, "Mouse");



	switch (type)
	{
	case 1:
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
		Ingame::stage = 3;
		Player::coloring_per = 0;
		OBJ->Add(new Enemy(12), "Boss")->pos = CENTER;
		enemy_count = 0;
		GameOver = false;
		break;
	}
	// 플레이어 추가 / 플레이어 찾기
	OBJ->Add(new Player, "player")->pos = { CENTER.x,float(B) };
	player = OBJ->Find("player");

	Ui_gst_tank = IMG->Add("gst_tank");
	Ui_gst_dive = IMG->Add("gst_dive");
	blind = IMG->Add("blind");
	Ui_base = IMG->Add("ui_ingame_base");
	Ui_pause = new Button(IMG->Add("ui_ingame_pause button"), { 80 , Y - 10 }, "", 60, 60, 0.2, [&]()->void {SCENE->Set("title"); });
	Ui_score = IMG->Add("ui_ingame_score");
	Ui_stage = IMG->Add("ui_ingame_stage");
	Ui_precent = IMG->Add("ui_ingame_%");
	Ui_abled_life = IMG->Add("ui_ingame_life");
	Ui_unabled_life = IMG->Add("ui_ingame_life2");
	Ui_time = IMG->Add("ui_ingame_time");
	Ui_timer_tank = IMG->Add("ui_ingame_time tank");
	Ui_timer_bar = IMG->Add("ui_ingame_time bar");
	game_over = new Window(IMG->Add("blind"), CENTER, 1600, 900);
	gov_box = IMG->Add("gov_box");

	OBJ->Add(new Mouse, "Mouse");

	timer = 60;
	playtime = TIME->Create(timer);

	boss = OBJ->Find("Boss");
	enemy[0] = OBJ->Find("Enemy1");
	enemy[1] = OBJ->Find("Enemy2");
	enemy[2] = OBJ->Find("Enemy3");

}

void Ingame::Update()
{
	if (player->hp <= 0)
	{
		GameOver = true;
		game_over->On();
		boss->flag = true;
		for (int i = 0; i < enemy_count; i++)
			enemy[i]->flag = true;
		playtime->flag = false;
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

	if (Player::coloring_per >= 1)
	{
		switch (type)
		{
		case 1:
			IMG->ReLoad("BG1");
			stage = 2;
			SCENE->Set("stage2");
			break;
		case 2:
			SCENE->Set("stage3");
			break;
		case 3:
			SCENE->Set("clear");
			break;
		}
	}
	// 플레이어가 y130자표 이상 올라가면 Ui 올라감.	Player.y < 200
	if (player->pos.y <= 130)
	{
		if (Y > -30)
		{
			Y -= 4;
			Ui_pause->pos.y -= 4;
		}
	}
	else
	{
		if (Y < 60)
		{
			Y += 4;
			Ui_pause->pos.y += 4;
		}
	}
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

	if (Ingame::GameOver)
	{
		if (box_size >= 1)
		{
			box_size -= 0.02;
			box_alpha -= 75;
		}
		else
			box_alpha = 255;

	}
}

void Ingame::Render()
{
	// GAMEOVER
	if (Ingame::GameOver)
	{
		gov_box->Render({ WINX / 2, WINY / 2 - 100 }, RT_ZERO, { box_size, box_size }, 0, 0.14, D3DCOLOR_RGBA(255, 255, 255, box_alpha));
	}

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
	else
	{
		char str[256];
		sprintf(str, "%d", Player::Score);		//스코어
		IMG->Write(str, { 290, Y - 32 }, 50, D3DCOLOR_XRGB(0, 0, 0), false);

		sprintf(str, "%.1f", Player::coloring_per);				//점령도
		IMG->Write(str, { WINX / 2 - 25, Y - 8 }, 50, D3DCOLOR_XRGB(0, 0, 0), true);
	}

	Ui_base->Render({ WINX / 2, Y }, RT_ZERO, { 1,1 }, 0, 0.3);
	Ui_score->Render({ 200, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.3);
	Ui_stage->Render({ 550,(Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.3);
	Ui_precent->Render({ WINX / 2 + 35, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.3);

	switch (player->hp)
	{
	case 1:
		Ui_unabled_life->Render({ WINX / 2 + 250, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.3);
		Ui_unabled_life->Render({ WINX / 2 + 180, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.3);
		Ui_abled_life->Render({ WINX / 2 + 110, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.3);
		break;
	case 2:
		Ui_unabled_life->Render({ WINX / 2 + 250, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.3);
		Ui_abled_life->Render({ WINX / 2 + 180, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.3);
		Ui_abled_life->Render({ WINX / 2 + 110, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.3);
		break;
	case 3:
		Ui_abled_life->Render({ WINX / 2 + 250, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.3);
		Ui_abled_life->Render({ WINX / 2 + 180, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.3);
		Ui_abled_life->Render({ WINX / 2 + 110, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.3);
		break;
	default:
		Ui_abled_life->Render({ WINX / 2 + 250, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.3);
		Ui_abled_life->Render({ WINX / 2 + 180, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.3);
		Ui_abled_life->Render({ WINX / 2 + 110, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.3);
		break;
	}
	Ui_time->Render({ WINX / 2 + 360, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.3);
	Ui_timer_tank->Render({ WINX / 2 + 600, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.3);
	RECT hprt =
	{
		0,
		0,
		Ui_timer_bar->info.Width / playtime->set * playtime->cur,
		Ui_timer_bar->info.Height
	};
	Ui_timer_bar->Render({ WINX / 2 + 605, (Y - 10) }, hprt, { 1,1 }, 0, 0.29);
}

void Ingame::Release()
{

}
