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

	Y = 150;
}

void WaitTitle::Update()
{
	if (INPUT->AnyKey())
	{
		SCENE->Set("title");
	}

	if (isDown)
	{
		if (Y < 180)
			Y += 0.4;
		else
			isDown = false;
	}
	else if (Y > 150)
	{
		Y -= 0.4;
	}
	else isDown = true;
}

void WaitTitle::Render()
{
	bg->CenterRender(CENTER);
	boy->CenterRender(V2(WINX / 2, Y));
	title->CenterRender(V2(WINX / 2, WINY / 2 + 150));
	press->CenterRender(V2(WINX / 2, WINY / 2 + 290));
	clock->CenterRender(V2(WINX / 2, 860));
}

void WaitTitle::Release()
{
}
