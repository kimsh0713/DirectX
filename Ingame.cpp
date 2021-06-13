#include "DXUT.h"
#include "Ingame.h"

extern int score;

Ingame::Ingame(int type)
	:type(type)
{
}

void Ingame::Init()
{
	// 마우스 추가
	OBJ->Add(new Mouse, "Mouse");


	Ui_base = IMG->Add("ui_ingame_base");
	Ui_pause = new Button(IMG->Add("ui_ingame_pause button"), { 80 , Y - 10}, "", 60, 60, 0.2, [&]()->void {SCENE->Set("title"); });
	Ui_score = IMG->Add("ui_ingame_score");

	OBJ->Add(new Mouse, "Mouse");

	switch (type)
	{
	case 1:
		Player::coloring_per = 0;
		OBJ->Add(new Enemy(7), "Boss")->pos = CENTER;
		score = 0;
		break;
	case 2:
		Player::coloring_per = 0;
		OBJ->Add(new Enemy(8), "Boss")->pos = CENTER;
	}
	// 플레이어 추가 / 플레이어 찾기
	OBJ->Add(new Player, "player")->pos = { CENTER.x,float(B) };
	player = OBJ->Find("player");

	OBJ->Add(new Enemy(1), "Eenmy")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
	OBJ->Add(new Enemy(2), "Eenmy")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
}

void Ingame::Update()
{
	// M 누르면 마우스 추가

	if (INPUT->Down('M'))
	{
		OBJ->Add(new Mouse, "Mouse");
	}

	if (Player::coloring_per >= 80)
	{
		switch (type)
		{
		case 1:
			IMG->ReLoad("BG1");
			SCENE->Set("clear");
			break;
		case 2:
			SCENE->Set("clear");
			break;
		}
	}
	// 플레이어가 y130자표 이상 올라가면 Ui 올라감.	Player.y < 200
	if (player->pos.y <= 130)
	{
		if (Y > -18)
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
}

void Ingame::Render()
{
	Ui_base->Render({ WINX / 2, Y }, RT_ZERO, { 1,1 }, 0, 0.2);
	Ui_score->Render({ 200, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.2);

	char str[256];
	sprintf(str, "%.0f", Player::coloring_per * 500);		//스코어
	IMG->Write(str, { 290, Y - 28 }, 40, D3DCOLOR_XRGB(0, 0, 0), false);
}

void Ingame::Release()
{

}
