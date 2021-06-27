#include "DXUT.h"
#include "Title.h"

Title::Title(int type)
	:bg(), map(), type(type)
{
}

void Title::Init()
{
	OBJ->Add(new Mouse, "Mouse");
	Ingame::GameClear = false;
	Ingame::GameOver = false;

	switch (type)
	{
	case 1:

		break;
	case 2:
		bg = IMG->Add("title_background");
		boy = IMG->Add("title_boy");
		clock = IMG->Add("title_clock");
		start = new Button(IMG->Add("title_button_start"), IMG->Add("title_button_start3"), { V2(WINX / 2 - 450, WINY / 2 + 55) }, "", 277, 145, 1, [&]()->void {SCENE->Set("stage1"); IMG->ReLoad("BG1"); IMG->ReLoad("BG3"); IMG->ReLoad("BG5"); });
		credit = new Button(IMG->Add("title_button_credit"), IMG->Add("title_button_credit3"), { V2(WINX / 2, WINY / 2 + 55) }, "", 277, 145, 1, [&]()->void {win_credit->On(); iswindow = true; });
		howto = new Button(IMG->Add("title_button_howto"), IMG->Add("title_button_howto3"), { V2(WINX / 2 + 450, WINY / 2 + 55) }, "", 277, 145, 1, [&]()->void {win_howto->On(); iswindow = true; });
		exit = new Button(IMG->Add("title_button_exit"), IMG->Add("crsron_exit"), { V2(100, WINY - 110) }, "", 110, 110, 1, [&]()->void {PostQuitMessage(0); });
		setting = new Button(IMG->Add("title_button_setting"), IMG->Add("crsron_setting"), { V2(WINX - 100, WINY - 110) }, "", 110, 110, 1, [&]()->void {});
		win_credit = new Window(IMG->Add("credit screen"), CENTER, 900, 900);
		win_howto = new Window(IMG->Add("howtoplay screen"), CENTER, 900, 900);
		eb_anim = vector<Texture*>
		{
			IMG->Add("eb1"),
			IMG->Add("eb2"),
			IMG->Add("eb3"),
			IMG->Add("eb4"),
			IMG->Add("eb5"),
		};
		sh_anim = vector<Texture*>
		{
			IMG->Add("sh1"),
			IMG->Add("sh2"),
			IMG->Add("sh3"),
			IMG->Add("sh4"),
			IMG->Add("sh5"),
		};

		delay = TIME->Create(0.3);
		delay->Start();
		break;
	}
	Y = 100;
	Y2 = 860;
}

void Title::Update()
{
	start->b_pos.y = start->pos.y + 88;
	credit->b_pos.y = credit->pos.y + 88;
	howto->b_pos.y = howto->pos.y + 88;
	// M 누르면 마우스 추가
	if (INPUT->Down('M'))
	{
		OBJ->Add(new Mouse, "Mouse");
	}
	if (delay->IsStop())
	{
		if (index >= 4)
		{
			index = 0;
		}
		index++;
		delay->Start();
	}
	switch (type)
	{
	case 1:
		if (INPUT->Down(VK_RETURN))
			SCENE->Set("title");
		if (delay->IsStop())
		{
			index++;
			delay->Start();
			//if (index == eb_anim.size())
			//	SCENE->Set("title");
		}
		break;
	case 2:
		break;
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
	if (!win_credit->isOn && !win_howto->isOn)
		iswindow = false;
}

void Title::Render()
{
	bg->Render(CENTER, RT_ZERO, { 1,1 }, 0, 1, D3DCOLOR_RGBA(r, g, b, 255));
	if (!iswindow)
	{
		start->On();
		credit->On();
		howto->On();
		exit->On();
		setting->On();
		boy->CenterRender(V2(WINX / 2, Y));
		clock->CenterRender(V2(WINX / 2, Y2));
		r = 255;
		g = 255;
		b = 255;
	}
	else
	{
		start->Off();
		credit->Off();
		howto->Off();
		exit->Off();
		setting->Off();
		r = 120;
		g = 120;
		b = 120;
	}
	if (win_credit->isOn)
	{
		eb_anim[index]->Render({ 1060, WINY / 2 + 50 }, RT_ZERO, { 1,1 }, 0, 0);
		sh_anim[index]->Render({ 570, WINY / 2 + 50 }, RT_ZERO, { 1,1 }, 0, 0);
	}
}

void Title::Release()
{
	SAFE_DELETE(map);
}
