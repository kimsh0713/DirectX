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
		img = IMG->Add("squid_bullet");
		speed = 5;
		break;
	}
	main_col = new Col(this, EATK);
}

void Bullet::Update()
{
	pos += dir * speed;
	main_col->Set(pos, 40, 40);
}

void Bullet::Render()
{
	for (auto& i : fxs)
		i->Render();
	if (!Ingame::GameOver && !Ingame::GameClear)
		img->Render(pos, { 0,0,0,0 }, { 1,1 }, 0, 1, D3DCOLOR_RGBA(255, 255, 255, 255));
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
