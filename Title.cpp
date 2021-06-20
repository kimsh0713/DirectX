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
		//anim = vector<Texture*>
		//{
		//	IMG->Add("1"),
		//	IMG->Add("2"),
		//	IMG->Add("3"),
		//	IMG->Add("4"),
		//	IMG->Add("5"),
		//};

		//delay = TIME->Create(0.3);
		//delay->Start();

		bg = IMG->Add("title_background");
		boy = IMG->Add("title_boy");
		clock = IMG->Add("title_clock");
		start = new Button(IMG->Add("title_button_start"), { V2(WINX / 2 - 450, WINY / 2 + 125) }, "", 300, 150, 1, [&]()->void {SCENE->Set("stage1"); IMG->ReLoad("BG1"); });
		credit = new Button(IMG->Add("title_button_credit"), { V2(WINX / 2, WINY / 2 + 125) }, "", 300, 150, 1, [&]()->void {win_credit->On(); });
		howto = new Button(IMG->Add("title_button_howto"), { V2(WINX / 2 + 450, WINY / 2 + 125) }, "", 300, 150, 1, [&]()->void {});
		exit = new Button(IMG->Add("title_button_exit"), { V2(100, WINY - 110) }, "", 110, 110, 1, [&]()->void {PostQuitMessage(0); });
		setting = new Button(IMG->Add("title_button_setting"), { V2(WINX - 100, WINY - 110) }, "", 110, 110, 1, [&]()->void {});
		win_credit = new Window(IMG->Add("credit screen"), CENTER, 900, 900);
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
	//if (delay->IsStop())
	//{
	//	if (index >= 4)
	//	{
	//		index = 0;
	//	}
	//	index++;
	//	delay->Start();
	//}
	switch (type)
	{
	case 1:
		if (INPUT->Down(VK_RETURN))
			SCENE->Set("title");
		if (delay->IsStop())
		{
			index++;
			delay->Start();
			if (index == anim.size())
				SCENE->Set("title");
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
	bg->Render(CENTER, RT_ZERO, {1,1},0,1,D3DCOLOR_RGBA(r,g,b,255));
	//anim[index]->Render();
	if (!win_credit->isOn)
	{
		start->isOn = true;
		credit->isOn = true;
		howto->isOn = true;
		boy->CenterRender(V2(WINX / 2, Y));
		clock->CenterRender(V2(WINX / 2, Y2));
		r = 255;
		g = 255;
		b = 255;
	}
	else if(win_credit->isOn)
	{
		start->isOn = false;
		credit->isOn = false;
		howto->isOn = false;
		r = 120;
		g = 120;
		b = 120;
	}
}

void Title::Release()
{
	SAFE_DELETE(map);
}
