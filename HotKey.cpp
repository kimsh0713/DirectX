#include "DXUT.h"
#include "HotKey.h"

extern int score;

HotKey::HotKey()
	:player(OBJ->Find("player"))
{
}

void HotKey::F1()
{
	((Player*)player)->NoDamage();
}

void HotKey::F2()
{
	int r = RANDOM->INT(1, 4);
	switch (r)
	{
	case 1:
		player->speed = 4;
		break;
	case 2:
		((Player*)player)->def++;
		break;
	case 3:
		F1();
		break;
	case 4:
		F3();
		break;
	}
}

void HotKey::F3()
{
	if (player->hp < 5)
		player->hp++;
	else
		score += 50;
}

void HotKey::F4()
{
	// goto menu
}

void HotKey::F5()
{
	SCENE->Set("stage1");
}

void HotKey::F6()
{
	SCENE->Set("stage2");
}
