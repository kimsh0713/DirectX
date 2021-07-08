#include "DXUT.h"
#include "Effect.h"

Effect::Effect(Texture* fx, V2 pos, int rot, int flag)
	:fx(fx), size{ 1,1 }, pos(pos), flag(flag), rot(rot), alpha(255)
{
}

void Effect::Render()
{
	if (alpha <= 0 || size.x <= 0 || size.y <= 0)
	{
		alpha = 0;
		size = { 0,0 };
		return;
	}
	timer += DT;
	if (timer > 0.1)
	{
		switch (flag)
		{
		case 1:
			alpha -= 15;
			size -= {0.1f, 0.1f};
			pos.y -= 3;
			break;
		}
		timer = 0;
	}

	fx->Render(pos, { 0,0,0,0 }, size, rot, 0, D3DCOLOR_RGBA(255, 255, 255, alpha));
}
