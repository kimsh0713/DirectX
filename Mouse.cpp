#include "DXUT.h"
#include "Mouse.h"

void Mouse::Init()
{
	main_col = new Col(this, MOUSE);
}

void Mouse::Update()
{
	pos = INPUT->GetMousePos();
	main_col->Set(pos, 10, 10);
}

void Mouse::Render()
{
	main_col->Draw();
}

void Mouse::Release()
{
	SAFE_DELETE(main_col);
}

void Mouse::Enter(Col* p)
{
}

void Mouse::Stay(Col* p)
{
}

void Mouse::Exit(Col* p)
{
}
