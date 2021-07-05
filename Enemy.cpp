#include "DXUT.h"
#include "Enemy.h"

Enemy::Enemy(int type)
	:type(type)
{
}

void Enemy::Flash()
{
	//dir = RANDOM->Vec2(pos);

	//fxs.emplace_back(new Effect(img, pos, 0, 4));

	//pos += dir * 50;
}

void Enemy::Rush()
{
	//during->Start();
	//char str[256];
	//sprintf(str, "enemy%d_red", type);
	//img = IMG->Add(str);
}

void Enemy::Shot(int shots)
{
	int angle = 360 / shots;
	for (int i = 0; i < 360; i += angle)
		OBJ->Add(new Bullet(1, { cos(D3DXToRadian(i)), sin(D3DXToRadian(i)) }), "Bullet")->pos = pos;
}

void Enemy::Init()
{
	dir = RANDOM->Vec2(pos);
	char str[256];
	sprintf(str, "enemy%d", type);
	img = IMG->Add(str);
	cool = 0;
	speed = 0;
	size = { 1,1 };
	rot = 0;
	spin_force = 0;
	front = 1;
	main_col = new Col(this, EATK);

	switch (type)
	{
	case 1:
		cool = 5;
		size = sizes[4];
		speed = 0.2;
		break;
	case 2:
		size = sizes[2];
		speed = 0.75;
		break;
	case 3:
		size = sizes[4];
		speed = 1.25;
		break;
	case 4:
		cool = 3;
		size = sizes[5];
		speed = 2;
		break;
	case 5:
		size = sizes[4];
		speed = 0.2;
		break;
	case 7:
		size = sizes[6];
		speed = 1.6;
		break;
	case 8:
		size = sizes[7];
		speed = 2.25;
		break;
	case 10:
		size = sizes[7];
		speed = 1.25;
		break;
	case 11:
		size = sizes[7];
		speed = 2;
		break;
	case 12:
		size = sizes[7];
		speed = 0.75;
		break;
	}

	timer = TIME->Create(cool);
	timer->Start();
	during = TIME->Create(3);
}

void Enemy::Update()
{
	if (Ingame::GameStart)
	{
		for (int i = 0; i < speed; i++)
			pos += dir;
	}

	spin_force += DT * 100;
	if (spin_force >= 360)
		spin_force = 0;

	int range = 7;

	char str[256];
	if (Ingame::GameStart)
	{
		t += DT;
		t2 += DT;
		t3 += DT;
	}
	if (t > 0.3)
	{
		if (E_type[0] < 4)
			E_type[0]++;
		else
			E_type[0] = 1;
		t = 0;
	}
	if (t2 > 0.7)
	{
		if (E_type[1] < 4)
			E_type[1]++;
		else
			E_type[1] = 1;
		t2 = 0;
	}
	if (t3 > 0.2)
	{
		if (E_type[2] < 4)
			E_type[2]++;
		else
			E_type[2] = 1;
		t3 = 0;
	}
	switch (type)
	{
	case 1:
		range = 30;
		sprintf(str, "거북이%d", E_type[0]);
		img = IMG->Add(str);
		break;
	case 2:
		range = 30;
		sprintf(str, "조개%d", E_type[0]);
		img = IMG->Add(str);
		break;
	case 3:
		range = 30;
		sprintf(str, "나비고기%d", E_type[0]);
		img = IMG->Add(str);
		break;
	case 4:
		range = 30;
		sprintf(str, "청새치%d", E_type[0]);
		img = IMG->Add(str);
		break;
	case 5:
		range = 30;
		sprintf(str, "해파리%d", E_type[1]);
		img = IMG->Add(str);
		break;
	case 7:
		sprintf(str, "boss_오징어%d", E_type[0]);
		img = IMG->Add(str);
		range = 110;
		break;
	case 8:
		sprintf(str, "boss_상어등%d", E_type[2]);
		img = IMG->Add(str);
		range = 70;
		break;
	case 10:
		sprintf(str, "덤보문어%d", E_type[2]);
		img = IMG->Add(str);
		range = 50;
		break;
	case 11:
		sprintf(str, "산갈치%d", E_type[2]);
		img = IMG->Add(str);
		range = 50;
		break;
	case 12:
		sprintf(str, "boss_초롱아귀%d", E_type[2]);
		img = IMG->Add(str);
		range = 110;
		break;
	}

	main_col->Set(pos, 16 * size.x, 16 * size.y);

	POINT c = { trunc(pos.x) - x_gap, trunc(pos.y) - y_gap };

	for (int y = -range; y <= range; y++)
	{
		for (int x = -range; x <= range; x++)
		{
			if (Player::cell[c.x + x][c.y + y] == 2)
			{
				dir = RANDOM->Vec2(pos);
			}
			if (Player::cell[c.x + x][c.y + y] == 1)
			{
				Player::isHurt = true;
			}
		}
	}

	if (Player::cell[c.x][c.y] == 3)
		if (type < 12)
			flag = true;

	V2 nextPos = pos + dir;
	rot = atan2(nextPos.y - pos.y, nextPos.x - pos.x);

	if (dir.x > 0)
		front = -1;
	else
		front = 1;
}

void Enemy::Render()
{
	main_col->Draw();
	//rot += spin_force;
	//if (rot >= 360)
	//	rot = 0;
	switch (type)
	{
	case 7:
		img->Render(pos, { 0,0,0,0 }, { 1,1 }, D3DXToRadian(90) + rot, 0.39);
		break;
	case 8:
		img->Render(pos, { 0,0,0,0 }, { 1,front }, D3DXToRadian(-90), 0.39);
		break;
	case 12:
		img->Render(pos, { 0,0,0,0 }, { 1,1 }, D3DXToRadian(90) + rot, 0.39);
		break;
	default:
		img->Render(pos, { 0,0,0,0 }, { 1,1 }, D3DXToRadian(90) + rot, 0.4);
		break;
	}
}

void Enemy::Release()
{
	SAFE_DELETE(main_col);
	for (auto& i : fxs)
		SAFE_DELETE(i);
	fxs.clear();
}

void Enemy::Enter(Col* p)
{
}

void Enemy::Stay(Col* p)
{
}

void Enemy::Exit(Col* p)
{
}
