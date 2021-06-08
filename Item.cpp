#include "DXUT.h"
#include "Item.h"

Item::Item(int type)
	:img(), type(type)
{
}

void Item::Init()
{
	main_col = new Col(this, ITEM);
	dir = RANDOM->Vec2(pos);

	switch (type)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		type = RANDOM->INT(1, 4);
		break;
	}
}

void Item::Update()
{
	pos += dir;

	int range = 7;

	for (int y = -range; y <= range; y++)
		for (int x = -range; x <= range; x++)
			if (pos.x + x <= L || pos.x + x >= R || pos.y + y <= T || pos.y + y >= B)
				dir = RANDOM->Vec2(pos);

	main_col->Set(pos, 50, 50);
}

void Item::Render()
{
	main_col->Draw();
}

void Item::Release()
{
	SAFE_DELETE(main_col);
}

void Item::Enter(Col* p)
{
}

void Item::Stay(Col* p)
{
}

void Item::Exit(Col* p)
{
}
