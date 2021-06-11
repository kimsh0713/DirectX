#include "DXUT.h"
#include "Ingame.h"

extern int score;

Ingame::Ingame(int type)
	:type(type)
{
}

void Ingame::Init()
{
	// �÷��̾� �߰� / �÷��̾� ã��

	Ui_base = IMG->Add("ui_ingame_base");
	Ui_pause = new Button(IMG->Add("ui_ingame_pause button"), { 80 , Y - 10}, "", 60, 60, 0.2, [&]()->void {SCENE->Set("title"); });

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
	OBJ->Add(new Player, "player")->pos = { CENTER.x,float(B) };
	player = OBJ->Find("player");

	OBJ->Add(new Enemy(1), "Eenmy")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
	OBJ->Add(new Enemy(2), "Eenmy")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
}

void Ingame::Update()
{
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
	// �÷��̾ y130��ǥ �̻� �ö󰡸� Ui �ö�.	Player.y < 200
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
}

void Ingame::Release()
{

}
