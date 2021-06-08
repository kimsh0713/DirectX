#include "DXUT.h"
#include "Bullet.h"

Bullet::Bullet(int type, V2 dir)
	:type(type), dir(dir), speed(0)
{
}

void Bullet::Init()
{
	switch (type)
	{
	case 1:
		img = IMG->Add("player");
		speed = 2;
		break;
	}
	main_col = new Col(this, EATK);
	delay = TIME->Create(0.5f);
	delay->Start();
}

void Bullet::Update()
{
	if (delay->IsStop())
	{
		fxs.emplace_back(new Effect(img, pos, 0, 3));
		delay->Start();
	}

	pos += dir * speed;
	main_col->Set(pos, 15, 15);

	int range = 3;
	V2 c = { trunc(pos.x) - 460, trunc(pos.y) - 40 };

	for (int y = -range; y <= range; y++)
		for (int x = -range; x <= range; x++)
			if (Player::cell[int(c.x) + x][int(c.y) + y] == 3)
				flag = true;
	if (pos.x < L || R < pos.x || pos.y < T || B < pos.y)
		flag = true;
}

void Bullet::Render()
{
	for (auto& i : fxs)
		i->Render();
	img->Render(pos, { 0,0,0,0 }, { 1,1 }, 0, 0, D3DCOLOR_RGBA(255, 0, 0, 255));
}

void Bullet::Release()
{
	SAFE_DELETE(main_col);
	for (auto& i : fxs)
		SAFE_DELETE(i);
	fxs.clear();
}

void Bullet::Enter(Col* p)
{
}

void Bullet::Stay(Col* p)
{
}

void Bullet::Exit(Col* p)
{
}
