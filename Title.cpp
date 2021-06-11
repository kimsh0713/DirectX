#include "DXUT.h"
#include "Title.h"

Title::Title(int type)
	:bg(), map(), type(type)
{
}

void Title::Init()
{
	OBJ->Add(new Mouse, "Mouse");


	/*map = new ScrollMap(IMG->Add("Bg", "Bg"));*/

	switch (type)
	{
	case 1:
		anim = vector<Texture*>
		{
			IMG->Add("intro1"),
			IMG->Add("intro2"),
			IMG->Add("intro3"),
			IMG->Add("intro4"),
			IMG->Add("intro5"),
		};

		delay = TIME->Create(1);
		delay->Start();
		break;
	case 2:
		bg = IMG->Add("title_background");
		boy = IMG->Add("title_boy");
		clock = IMG->Add("title_clock");
		start = new Button(IMG->Add("title_button_start"), { V2(WINX / 2 - 450, WINY / 2 + 125) }, "", 300, 150, 1, [&]()->void {SCENE->Set("stage1"); IMG->ReLoad("BG1"); });
		credit = new Button(IMG->Add("title_button_credit"), { V2(WINX / 2, WINY / 2 + 125) }, "", 300, 150, 1, [&]()->void { });
		howto = new Button(IMG->Add("title_button_howto"), { V2(WINX / 2 + 450, WINY / 2 + 125) }, "", 300, 150, 1, [&]()->void { });
		exit = new Button(IMG->Add("title_button_exit"), { V2(100, WINY - 110) }, "", 110, 110, 1, [&]()->void {PostQuitMessage(0); });
		setting = new Button(IMG->Add("title_button_setting"), { V2(WINX - 100, WINY - 110) }, "", 110, 110, 1, [&]()->void { });
		win_credit = new Window(IMG->Add("HowToPlay"), CENTER, 900, 900);
		break;
	}
}

void Title::Update()
{
	if (INPUT->Down('M'))
	{
		OBJ->Add(new Mouse, "Mouse");
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
			if (index == anim.size())
				SCENE->Set("title");
		}
		break;
	case 2:
		break;
	}
}

void Title::Render()
{
	bg->Render();
	boy->CenterRender(V2(WINX / 2, WINY / 2 - 250));
	clock->CenterRender(V2(WINX / 2, WINY - 40));
}

void Title::Release()
{
	SAFE_DELETE(map);
}
