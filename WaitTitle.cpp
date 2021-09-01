#include "DXUT.h"
#include "WaitTitle.h"

void WaitTitle::Init()
{
	bg = IMG->Add("title_background");
	boy = IMG->Add("title_boy");
	title = IMG->Add("title_title name");
	press = IMG->Add("title_press abts");
	clock = IMG->Add("title_clock");

	OBJ->Add(new Mouse, "Mouse");

	Y = 110;
	Y2 = 860;

	Back_Ground_music = SOUND->Add("BackGround_music", L"Sea Of Sun");
	Back_Ground_music->Play(1);
}

void WaitTitle::Update()
{
	if (INPUT->AnyKey())
	{
		SCENE->Set("title");
	}
	i += 0.025;
	Y += sin(i);



	if (isDown2)
	{
		if (Y2 < 880)
			Y2 += 0.17;
		else
			isDown2 = false;
	}
	else if (Y2 > 850)
	{
		Y2 -= 0.2;
	}
	else
		isDown2 = true;
	switch (index)
	{
	case 0:
		if (alpha < 240)
			alpha += 15;
		else index++;
		break;
	case 1:
		if (alpha > 15)
			alpha -= 15;
		else index = 0;
		break;
	}

}

void WaitTitle::Render()
{
	bg->CenterRender(CENTER);
	boy->CenterRender(V2(WINX / 2, Y));
	title->CenterRender(V2(WINX / 2, WINY / 2 + 150));
	press->CenterRender(V2(WINX / 2, WINY / 2 + 290), 0, { 1,1 }, D3DCOLOR_RGBA(255,255,255,alpha));
	clock->CenterRender(V2(WINX / 2, Y2));
}

void WaitTitle::Release()
{
}
