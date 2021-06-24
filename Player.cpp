#include "DXUT.h"
#include "Player.h"

extern float time_scale;

int Player::cell[CELLSIZE_X][CELLSIZE_Y] = { 0, };
float Player::coloring_per = 0;
bool Player::isHurt = false;

void Player::Init()
{
	boss = OBJ->Find("Boss");

	switch (Ingame::stage)
	{
	case 1:
		bg = IMG->Add("BG1");
		bg2 = IMG->Add("BG2");
		break;
	case 2:
		bg = IMG->Add("BG3");
		bg2 = IMG->Add("BG4");
		break;
	case 3:
		bg = IMG->Add("BG5");
		bg2 = IMG->Add("BG6");
		break;
	}


	img = IMG->Add("player");
	Over = IMG->Add("GAMEOVER");

	D3DLOCKED_RECT lr;

	bg->p->LockRect(0, &lr, 0, D3DLOCK_DISCARD);

	DWORD* pixel = (DWORD*)lr.pBits;

	for (int y = CELLSIZE_Y - 1; y != -1; --y)
		for (int x = CELLSIZE_X - 1; x != -1; --x)
			bg_color[y * CELLSIZE_X + x] = pixel[y * CELLSIZE_X + x];

	bg->p->UnlockRect(0);

	memset(cell, 0, sizeof(cell));

	for (size_t x = 0; x < CELLSIZE_X; x++)
		for (size_t y = 0; y < CELLSIZE_Y; y++)
			if (x == 0 || x == CELLSIZE_X - 1 || y == 0 || y == CELLSIZE_Y - 1)
				cell[x][y] = 1;

	coloring_per = 0;
	coloring_cells = 0;
	temp = 0;

	draw_mode = true;
	DrawArea();

	main_col = new Col(this, P);
	during = TIME->Create(2);

	speed = 3;
	rot = 0;
	hp = 3;
	def = 0;
	draw_mode = false;
	no_damage = false;
	last = { 0,0 };
}

void Player::Update()
{
	switch (Ingame::stage)
	{
	case 1:
		bg = IMG->Add("BG1");
		bg2 = IMG->Add("BG2");
		break;
	case 2:
		bg = IMG->Add("BG3");
		bg2 = IMG->Add("BG4");
		break;
	case 3:
		bg = IMG->Add("BG5");
		bg2 = IMG->Add("BG6");
		break;
	}
	if (isHurt)
	{
		Hurt();
	}
	if (hp <= 0)
	{
		IMG->ReLoad("BG1");
		SCENE->Set("fail");
	}


	main_col->Set(pos, 5, 5);

	spin_force += DT * 100;
	if (spin_force >= 360)
		spin_force = 0;

	//if (during->IsStop())
	//{
	//	rot = 0;
	//	no_damage = false;
	//	img = IMG->Add("player");
	//}
	//else
	//{
	//	no_damage = true;
	//	rot += spin_force;
	//	if (rot >= 360)
	//		rot = 0;
	//}

	if (Ingame::GameStart == true)
	{
		InputKey();
	}
}

void Player::Render()
{
	main_col->Draw();
	bg2->Render(CENTER, RT_ZERO, { 1,1 }, 0, 1);
	bg->Render(CENTER, RT_ZERO, { 1,1 }, 0, 1);
	img->Render(pos, RT_ZERO, { 1,1 }, D3DXToRadian(rot));
	POINT c = { pos.x, pos.y };
	char str[256];
	sprintf(str, "%d", cell[c.x][c.y]);		//½ºÄÚ¾î
	IMG->Write(str, { 290, WINY/2 }, 50, D3DCOLOR_XRGB(0, 0, 0), false);
}

void Player::Release()
{
	SAFE_DELETE(main_col);
}

void Player::Enter(Col* p)
{
	switch (p->tag)
	{
	case EATK:
		if (!no_damage)
		{
			if (Current() == 1 || Current() == 0)
			{
				if (def > 0)
					def--;
				else
				{
					hp--;
					speed = 3;
					pos = start;
					DrawArea(2);
				}
			}
		}
		break;
	case ITEM:
		switch (((Item*)p->owner)->type)
		{
		case 1:
			speed = 4;
			break;
		case 2:
			def++;
			break;
		case 3:
			NoDamage();
			break;
		case 4:
			HOT->F3();
			break;
		}
		p->owner->flag = true;
		break;
	}
}

void Player::Stay(Col* p)
{
	switch (p->tag)
	{
	case OBS:
		switch (key)
		{
		case Player::KeyState::UP:
			pos.y++;
			break;
		case Player::KeyState::DOWN:
			pos.y--;
			break;
		case Player::KeyState::LEFT:
			pos.x++;
			break;
		case Player::KeyState::RIGHT:
			pos.x--;
			break;
		}
		break;
	}
}

void Player::Exit(Col* p)
{

}

void Player::SetUp()
{

}

void Player::reset()
{
	DrawArea(3);
}

void Player::InputKey()
{
	if (INPUT->Press('W'))
	{
		pos.y -= 2;
	}
	if (INPUT->Press(VK_UP))
	{
		rot = 0;
		for (size_t i = 0; i < speed; i++)
		{
			key = KeyState::UP;

			POINT c = { pos.x, pos.y };
			if (cell[c.x][c.y - 1] == 0)
			{
				if (!INPUT->Press(VK_SPACE))
				{
					return;
				}
			}
			if (cell[c.x][c.y - 2] == 1)
				return;
			if (cell[c.x][c.y - 1] == 3)
				return;

			pos.y--;

			if (pos.y < T)
				pos.y = T;

			if (Current() == 2)
				DrawArea();
			else
				if (!Near(key, 3))
					DrawLine();
		}
	}

	else if (INPUT->Press(VK_DOWN))
	{
		rot = 180;
		for (size_t i = 0; i < speed; i++)
		{
			key = KeyState::DOWN;

			POINT c = { pos.x, pos.y };
			if (cell[c.x][c.y + 1] == 0)
			{
				if (!INPUT->Press(VK_SPACE))
				{
					return;
				}
			}
			if (cell[c.x][c.y + 2] == 1)
				return;
			if (cell[c.x][c.y + 1] == 3)
				return;

			pos.y++;

			if (pos.y > B)
				pos.y = B;

			if (Current() == 2)
				DrawArea();
			else
				if (!Near(key, 3))
					DrawLine();
		}
	}

	else if (INPUT->Press(VK_LEFT))
	{
		rot = 270;
		for (size_t i = 0; i < speed; i++)
		{
			key = KeyState::LEFT;

			POINT c = { pos.x, pos.y };
			if (cell[c.x - 1][c.y] == 0)
			{
				if (!INPUT->Press(VK_SPACE))
				{
					return;
				}
			}
			if (cell[c.x - 2][c.y] == 1)
				return;
			if (cell[c.x - 1][c.y] == 3)
				pos.x+= 3;

			pos.x--;

			if (pos.x < L)
				pos.x = L;

			if (Current() == 2)
				DrawArea();
			else
				if (!Near(key, 3))
					DrawLine();
		}

	}

	else if (INPUT->Press(VK_RIGHT))
	{
		rot = 90;
		for (size_t i = 0; i < speed; i++)
		{
			key = KeyState::RIGHT;

			POINT c = { pos.x, pos.y };
			if (cell[c.x + 1][c.y] == 0)
			{
				if (!INPUT->Press(VK_SPACE))
				{
					return;
				}
			}
			if (cell[c.x + 2][c.y] == 1)
				return;
			if (cell[c.x + 1][c.y] == 3)
				return;

			pos.x++;

			if (pos.x > R - 1)
				pos.x = R - 1;

			if (Current() == 2)
				DrawArea();
			else
				if (!Near(key, 3))
					DrawLine();
		}
	}
	if (INPUT->Down(VK_F8))
		coloring_per = 100;

	if (INPUT->Down(VK_F1))
		HOT->F1();
	if (INPUT->Down(VK_F2))
		HOT->F2();
	if (INPUT->Down(VK_F3))
		HOT->F3();
	if (INPUT->Down(VK_F4))
		HOT->F4();
	if (INPUT->Down(VK_F5))
		HOT->F5();
	if (INPUT->Down(VK_F6))
		HOT->F6();
}

void Player::Hurt()
{
	pos = start;
	speed = 3;
	for (int x = CELLSIZE_X - 1; x != -1; --x)
	{
		for (int y = CELLSIZE_Y - 1; y != -1; --y)
		{
			if (cell[x][y] == 1)
			{
				DrawArea(2);
				hp -= 1;
				isHurt = false;
			}
		}
	}
}

void Player::DrawLine()
{
	draw_mode = true;

	D3DLOCKED_RECT lr;

	bg->p->LockRect(0, &lr, 0, D3DLOCK_DISCARD);

	DWORD* pixel = (DWORD*)lr.pBits;

	POINT c = { pos.x - x_gap,pos.y - y_gap };
	int index = c.y * CELLSIZE_X + c.x;

	cell[c.x][c.y] = 1;

	pixel[index] = D3DCOLOR_RGBA(0, 0, 255, 255);

	bg->p->UnlockRect(0);
}

void Player::DrawArea(int draw_flag)
{
	if (!draw_mode)
	{
		start = pos;
		return;
	}

	draw_mode = false;

	D3DLOCKED_RECT lr;

	bg->p->LockRect(0, &lr, 0, D3DLOCK_DISCARD);

	DWORD* pixel = (DWORD*)lr.pBits;

	for (int y = CELLSIZE_Y - 1; y != -1; --y)
	{
		for (int x = CELLSIZE_X - 1; x != -1; --x)
		{
			D3DXCOLOR change = bg_color[y * CELLSIZE_X + x];

			if (cell[x + 1][y] == 3 && cell[x - 1][y] == 3)
			{
				change = D3DCOLOR_RGBA(0, 0, 0, 0);
				cell[x][y] = 3;
			}
			if (cell[x][y + 1] == 3 && cell[x][y - 1] == 3)
			{
				change = D3DCOLOR_RGBA(0, 0, 0, 0);
				cell[x][y] = 3;
			}
			if ((x == 0 && cell[x + 1][y] == 3) ||
				(x == CELLSIZE_X - 1 && cell[x - 1][y] == 3) ||
				(y == 0 && cell[x][y + 1] == 3) ||
				(y == CELLSIZE_Y - 1 && cell[x][y - 1] == 3))
			{
				change = D3DCOLOR_RGBA(0, 0, 0, 0);
				cell[x][y] = 3;
			}
			switch (cell[x][y])
			{
			case 0:
				change = bg_color[y * CELLSIZE_X + x];
				break;
			case 1:
				if (draw_flag == 2 || draw_flag == 3)
				{
					change = bg_color[y * CELLSIZE_X + x];
					cell[x][y] = 0;
					break;
				}
				change = D3DCOLOR_RGBA(0, 0, 0, 255);
				cell[x][y] = 2;

				last = { float(x),float(y) };

				coloring_cells++;
				break;
			case 2:
				change = D3DCOLOR_RGBA(255, 0, 0, 255);
				break;
			case 3:
				if (draw_flag == 3)
				{
					change = bg_color[y * CELLSIZE_X + x];
					cell[x][y] = 0;
					break;
				}
				if (cell[x][y] == 3)
					change = D3DCOLOR_RGBA(0, 0, 0, 0);
			}

			pixel[y * CELLSIZE_X + x] = change;
		}
	}

	bg->p->UnlockRect(0);

	if (draw_flag != 1)
		AutoFill();
}

bool Player::FloodFill(V2 pos, int target, int change)
{
	if (target == change) return true;
	if (cell[(int)pos.x][(int)pos.y] != target) return true;

	if (int(pos.x) < 0 || int(pos.y) < 0 || int(pos.x) > CELLSIZE_X - 1 || int(pos.y) > CELLSIZE_Y - 1) return true;

	queue<V2> v2q;

	bool add = false;
	temp = 0;

	if (change == 3)
		add = true;

	cell[(int)pos.x][(int)pos.y] = change;

	v2q.push(pos);

	if (add)
		temp++;

	while (!v2q.empty())
	{
		V2 n = v2q.front();
		v2q.pop();

		if (n.x == (int)(boss->pos.x - x_gap) &&
			n.y == (int)(boss->pos.y - y_gap))
			return false;
		if (cell[(int)n.x - 1][(int)n.y] == target)
		{
			cell[(int)n.x - 1][(int)n.y] = change;
			v2q.push({ n.x - 1, n.y });
			if (add)
				temp++;
		}
		if (cell[(int)n.x + 1][(int)n.y] == target)
		{
			cell[(int)n.x + 1][(int)n.y] = change;
			v2q.push({ n.x + 1, n.y });
			if (add)
				temp++;
		}
		if (cell[(int)n.x][(int)n.y - 1] == target)
		{
			cell[(int)n.x][(int)n.y - 1] = change;
			v2q.push({ n.x, n.y - 1 });
			if (add)
				temp++;
		}
		if (cell[(int)n.x][(int)n.y + 1] == target)
		{
			cell[(int)n.x][(int)n.y + 1] = change;
			v2q.push({ n.x, n.y + 1 });
			if (add)
				temp++;
		}
	}

	AddItem();

	coloring_cells += temp;

	float temp1 = coloring_cells * 100;
	coloring_per = temp1 / total_cell;

	draw_mode = true;
	DrawArea(1);

	return true;
}

void Player::AutoFill()
{
	if (last == V2(0, 0))
		return;
	last = { 0,0 };

	V2 value[4];

	value[0] = { -1,-1 };
	value[1] = { 1,1 };
	value[2] = { -1,1 };
	value[3] = { 1,-1 };

	bool isOk[4];

	for (size_t i = 0; i < 4; i++)
		isOk[i] = FloodFill({ pos.x - x_gap + value[i].x ,pos.y - y_gap + value[i].y }, 0, 100);


	for (size_t i = 0; i < 4; i++)
		if (isOk[i])
			FloodFill({ pos.x - x_gap + value[i].x ,pos.y - y_gap + value[i].y }, 100, 3);
		else
			FloodFill({ pos.x - x_gap + value[i].x ,pos.y - y_gap + value[i].y }, 100, 0);

	draw_mode = true;
	DrawArea(1);
}

void Player::AddItem()
{
	//int temp_per = double(coloring_cells + temp) * 100 / total_cell - double(coloring_cells * 100) / total_cell;

	//for (size_t i = 0; i < temp_per % 2; i++)
	//	OBJ->Add(new Item(RANDOM->INT(1, 5)), "Item")->pos = { float(RANDOM->INT(L + 1, R - 1)),float(RANDOM->INT(T + 1, B - 1)) };
}

void Player::NoDamage()
{
	during->Start();
	img = IMG->Add("player1");
}

bool Player::Near(KeyState dir, int target)
{
	int cx = pos.x - x_gap;
	int cy = pos.y - y_gap;

	switch (dir)
	{
	case KeyState::UP:
		return cell[cx][cy - 1] == target;
		break;
	case KeyState::DOWN:
		return cell[cx][cy + 1] == target;
		break;
	case KeyState::LEFT:
		return cell[cx - 1][cy] == target;
		break;
	case KeyState::RIGHT:
		return cell[cx + 1][cy] == target;
		break;
	}
}

int Player::Current()
{
	return cell[int(pos.x - x_gap)][int(pos.y - y_gap)];
}
