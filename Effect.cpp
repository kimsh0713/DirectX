#include "DXUT.h"
#include "Effect.h"

Effect::Effect(Texture* fx, V2 pos, int rot, int flag)
	:fx(fx), size{ 1,1 }, pos(pos), flag(flag), rot(rot), alpha(255)
{
	delay = TIME->Create(0.1f);
	delay->Start();
}

void Effect::Render()
{
	if (alpha <= 0 || size.x <= 0 || size.y <= 0)
	{
		alpha = 0;
		size = { 0,0 };
		return;
	}

	if (delay->IsStop())
	{
		switch (flag)
		{
		case 1:
			alpha -= 30;
			break;
		case 2:
			size -= {0.1f, 0.1f};
			break;
		case 3:
			alpha -= 30;
			size -= {0.1f, 0.1f};
			break;
		case 4:
			alpha -= 30;
			size += {0.1f, 0.1f};
			break;
		}
		delay->Start();
	}

	fx->Render(pos, { 0,0,0,0 }, size, rot, 0, D3DCOLOR_RGBA(255, 255, 255, alpha));
}
