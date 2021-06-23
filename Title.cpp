#include "DXUT.h"
#include "Title.h"

Title::Title(int type)
	:bg(), map(), type(type)
{
}

void Title::Init()
{
	OBJ->Add(new Mouse, "Mouse");

	switch (type)
	{
	case 1:

		break;
	case 2:
		bg = IMG->Add("title_background");
		boy = IMG->Add("title_boy");
		clock = IMG->Add("title_clock");
		start = new Button(IMG->Add("title_button_start"), { V2(WINX / 2 - 450, WINY / 2 + 125) }, "", 300, 150, 1, [&]()->void {SCENE->Set("stage1"); IMG->ReLoad("BG1"); IMG->ReLoad("BG3"); IMG->ReLoad("BG5"); });
		credit = new Button(IMG->Add("title_button_credit"), { V2(WINX / 2, WINY / 2 + 125) }, "", 300, 150, 1, [&]()->void {win_credit->On(); });
		howto = new Button(IMG->Add("title_button_howto"), { V2(WINX / 2 + 450, WINY / 2 + 125) }, "", 300, 150, 1, [&]()->void {});
		exit = new Button(IMG->Add("title_button_exit"), { V2(100, WINY - 110) }, "", 110, 110, 1, [&]()->void {PostQuitMessage(0); });
		setting = new Button(IMG->Add("title_button_setting"), { V2(WINX - 100, WINY - 110) }, "", 110, 110, 1, [&]()->void {});
		win_credit = new Window(IMG->Add("credit screen"), CENTER, 900, 900);
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
}

void Title::Render()
{
	bg->Render(CENTER, RT_ZERO, { 1,1 }, 0, 1, D3DCOLOR_RGBA(r, g, b, 255));
	if (!win_credit->isOn)
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
	else if (win_credit->isOn)
	{
		start->Off();
		credit->Off();
		howto->Off();
		exit->Off();
		setting->Off();
		eb_anim[index]->Render({1060, WINY / 2 + 50}, RT_ZERO, {1,1},0,0);
		sh_anim[index]->Render({570, WINY / 2 + 50}, RT_ZERO, {1,1},0,0);
		r = 120;
		g = 120;
		b = 120;
	}
}

void Title::Release()
{
	SAFE_DELETE(map);
}
