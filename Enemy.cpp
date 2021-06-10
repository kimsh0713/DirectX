#include "DXUT.h"
#include "Enemy.h"

Enemy::Enemy(int type)
	:type(type)
{
}

void Enemy::Flash()
{
	dir = RANDOM->Vec2(pos);

	fxs.emplace_back(new Effect(img, pos, 0, 4));

	pos += dir * 50;
}

void Enemy::Rush()
{
	during->Start();
	char str[256];
	sprintf(str, "enemy%d_red", type);
	img = IMG->Add(str);
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
	main_col = new Col(this, EATK);

	switch (type)
	{
	case 1:
		cool = 5;
		size = sizes[3];
		speed = speeds[2];
		break;
	case 2:
		size = sizes[3];
		speed = speeds[1];
		break;
	case 3:
		//size = sizes[1];
		//speed = speeds[3];
		break;
	case 4:
		cool = 3;
		size = sizes[3];
		speed = speeds[3];
		break;
	case 5:
		size = sizes[0];
		speed = speeds[4];
		break;
	case 6:
		size = sizes[4];
		speed = speeds[0];
		break;
	case 7:
		cool = 10;
		size = sizes[5];
		speed = speeds[2];
		break;
	case 8:
		cool = 3;
		size = sizes[5];
		speed = speeds[2];
		break;
	}

	timer = TIME->Create(cool);
	timer->Start();
	during = TIME->Create(3);
}

void Enemy::Update()
{
	for (int i = 0; i < speed; i++)
		pos += dir;

	spin_force += DT * 100;
	if (spin_force >= 360)
		spin_force = 0;

	int range = 7;

	switch (type)
	{
	case 1:
	case 4:
		range = 30;
		if (timer->IsStop())
		{
			//Flash();
			timer->Start();
		}
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
		range = 110;
		if (timer->IsStop())
		{
			//Shot(36);
			timer->Start();
		}
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
		if (type < 7)
			flag = true;
}

void Enemy::Render()
{
	main_col->Draw();
	rot += spin_force;
	if (rot >= 360)
		rot = 0;
	img->Render(pos, { 0,0,0,0 }, { 1,1 }, D3DXToRadian(0), 0.3);
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
