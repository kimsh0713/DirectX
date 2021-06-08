#include "DXUT.h"
#include "Window.h"

Window::Window(Texture* bg, V2 pos, float w, float h)
	:bg(bg), exit(), isOn(false)
{
	this->pos = pos;

	float right = pos.x + w / 2, top = pos.y - h / 2;

	exit = new Button(IMG->Add("button_cross"), { right - 25,top + 25 }, "", 60, 60, 0, [&]()->void { Off(); });
	exit->Off();

	OBJ->Add(this, "Window");
}

void Window::On()
{
	isOn = true;
	exit->On();
}

void Window::Off()
{
	isOn = false;
	exit->Off();
}

void Window::Init()
{
}

void Window::Update()
{
}

void Window::Render()
{
	if (isOn)
		bg->Render(pos);
}

void Window::Release()
{
	exit->flag = true;
}

void Window::Enter(Col* p)
{
}

void Window::Stay(Col* p)
{
}

void Window::Exit(Col* p)
{
}
