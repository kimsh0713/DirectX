#include "DXUT.h"
#include "Ingame.h"

extern int score;

int Ingame::stage = 1;

Ingame::Ingame(int type)
	:type(type)
{
}

void Ingame::Init()
{
	// ���콺 �߰�
	OBJ->Add(new Mouse, "Mouse");


	Ui_base = IMG->Add("ui_ingame_base");
	Ui_pause = new Button(IMG->Add("ui_ingame_pause button"), { 80 , Y - 10 }, "", 60, 60, 0.2, [&]()->void {SCENE->Set("title"); });
	Ui_score = IMG->Add("ui_ingame_score");
	Ui_stage = IMG->Add("ui_ingame_stage");
	Ui_precent = IMG->Add("ui_ingame_%");

	OBJ->Add(new Mouse, "Mouse");

	switch (type)
	{
	case 1:
		Ingame::stage = 1;
		Player::coloring_per = 0;
		OBJ->Add(new Enemy(7), "Boss")->pos = CENTER;
		OBJ->Add(new Enemy(1), "Eenmy")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
		OBJ->Add(new Enemy(2), "Eenmy")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
		score = 0;
		break;
	case 2:
		Ingame::stage = 2;
		Player::coloring_per = 0;
		OBJ->Add(new Enemy(8), "Boss")->pos = CENTER;
		OBJ->Add(new Enemy(3), "Eenmy")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
		OBJ->Add(new Enemy(4), "Eenmy")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
		OBJ->Add(new Enemy(5), "Eenmy")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
	}
	// �÷��̾� �߰� / �÷��̾� ã��
	OBJ->Add(new Player, "player")->pos = { CENTER.x,float(B) };
	player = OBJ->Find("player");
}

void Ingame::Update()
{
	// M ������ ���콺 �߰�

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
	Ui_score->Render({ 200, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.2);
	Ui_stage->Render({ 550,(Y - 10) }, RT_ZERO, {1,1}, 0, 0.2);
	Ui_precent->Render({ WINX / 2 + 40, (Y - 10) }, RT_ZERO, { 1,1 }, 0, 0.2);

	char str[256];
	sprintf(str, "%.0f", Player::coloring_per * 500);		//���ھ�
	IMG->Write(str, { 290, Y - 28 }, 40, D3DCOLOR_XRGB(0, 0, 0), false);

	sprintf(str, "%.1f", Player::coloring_per);				//���ɵ�
	IMG->Write(str, { WINX / 2 - 25, Y - 10 }, 40, D3DCOLOR_XRGB(0, 0, 0), true);
}

void Ingame::Release()
{

}