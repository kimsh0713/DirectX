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
	sprintf(str, "enemy%d", type);		//사진 enemy 숫자		7,8은 보스
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
		speed = speeds[2];
		break;
	case 2:
		size = sizes[2];
		speed = speeds[1];
		break;
	case 3:
		size = sizes[4];
		speed = speeds[3];
		break;
	case 4:
		cool = 3;
		size = sizes[5];
		speed = speeds[3];
		break;
	case 5:
		size = sizes[4];
		speed = speeds[4];
		break;
	case 6:
		size = sizes[2];
		speed = speeds[0];
		break;
	case 7:
		size = sizes[6];
		speed = speeds[2];
		break;
	case 8:
		size = sizes[7];
		speed = speeds[4];
		break;
	case 9:
		size = sizes[7];
		speed = speeds[2];
		break;
	case 10:
		size = sizes[7];
		speed = speeds[2];
		break;
	case 11:
		size = sizes[7];
		speed = speeds[2];
		break;
	case 12:
		size = sizes[7];
		speed = speeds[3];
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

	switch (type)
	{
	case 1:
	case 6:
		range = 30;
		//if (timer->IsStop())
		//{
		//	Flash();
		//	timer->Start();
		//}
		break;
	case 7:
		range = 110;
		if (timer->IsStop())
		{
			//Rush();
			timer->Start();
		}
		if (during->IsStop())
		{
			char str[256];
			sprintf(str, "enemy%d", type);
			img = IMG->Add(str);
		}
		else
		{
			pos += dir * 10;
			fxs.emplace_back(new Effect(img, pos, rot, 3));
		}
		break;
	case 8:
		range = 70;
		break;
	case 9:
		range = 110;
		break;
	case 10:
		range = 30;
		break;
	case 11:
		range = 30;
		break;
	case 12:
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

	if (rot > 0)
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
	case 8:
		img->Render(pos, { 0,0,0,0 }, { 1,front }, D3DXToRadian(-90), 0.39);
		break;
	default:
		img->Render(pos, { 0,0,0,0 }, { 1,1 }, D3DXToRadian(90) + rot, 0.39);
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
