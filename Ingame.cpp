#include "DXUT.h"
#include "Ingame.h"

extern int score;

Ingame::Ingame(int type)
	:bg(), map(), type(type)
{
}

void Ingame::Init()
{
	OBJ->Add(new Mouse, "Mouse");

	Img = IMG->Add("stage");

	 //BackGround = IMG->Add("BackGround");

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

	for (size_t i = 0; i < enemy_count - 3; i++)
	{
		OBJ->Add(new Enemy(1), "Enemy")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
		//OBJ->Add(new Enemy(2), "Enemy")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
	}

	OBJ->Add(new Enemy(1),"Eenmy")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
	OBJ->Add(new Enemy(2),"Eenmy")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
	//OBJ->Add(new Enemy(3),"Eenmy")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1,B - 1)) };
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

	//if (map)
	//	map->Update(500);
}

void Ingame::Render()
{
	/*if (map)
		map->Render();*/
	//BackGround->Render();
	Img->Render({ CENTER.x - 650, CENTER.y - 400 }, RT_ZERO, { 1,1 }, 0, 0);
	
}

void Ingame::Release()
{
	SAFE_DELETE(map);
}
