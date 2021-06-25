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
	player->hp--;
}

void HotKey::F3()
{
	if (player->hp < 3)
		player->hp++;
	else
		Player::Score += 50;
}

void HotKey::F4()
{
	// goto menu
}

void HotKey::F5()
{
	IMG->ReLoad("BG1");
	Player::coloring_per = 80;
	//SCENE->Set("stage1");
}

void HotKey::F6()
{
	IMG->ReLoad("BG3");
	IMG->ReLoad("BG1");
	Ingame::stage = 2;
	SCENE->Set("stage2");
}
