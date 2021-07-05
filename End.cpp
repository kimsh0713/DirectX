#include "DXUT.h"
#include "End.h"

End::End(int type)
	:bg(), map(), type(type)
{
}

void End::Init()
{
	OBJ->Add(new Mouse, "Mouse");

	//map = new ScrollMap(IMG->Add("Bg"));

	bg = IMG->Add("title_background");
	game = IMG->Add("gov_game");
	clear = IMG->Add("gcl_clear");
	over = IMG->Add("gov_over");

	title = new Button(IMG->Add("gov_backbtn"), IMG->Add("gcl_backbtn_cson"), { CENTER.x ,CENTER.y + 200 }, "", 348, 176, 1, [&]()->void { SCENE->Set("title"); IMG->ReLoad("BG1"); IMG->ReLoad("BG3"); IMG->ReLoad("BG5"); Player::Score = 0; });
}

void End::Update()
{
	if (INPUT->Down('M'))
	{
		OBJ->Add(new Mouse, "Mouse");
	}
}

void End::Render()
{
	//if (map)
	//	map->Render();
	bg->Render();
	game->Render({ WINX / 2 - 320, WINY / 2 - 80 });
	switch (type)
	{
	case 1:
		clear->Render({ WINX / 2 + 320, WINY / 2 - 80 });
		break;
	case 2:
		over->Render({ WINX / 2 + 320, WINY / 2 - 80 });
		break;
	}
}

void End::Release()
{
	SAFE_DELETE(map);
}
