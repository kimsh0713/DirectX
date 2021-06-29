#include "DXUT.h"
#include "Window.h"

Window::Window(Texture* bg, V2 pos, float w, float h,V2 pos2)
	:bg(bg), exit(), isOn(false)
{
	this->pos = pos;

	float right = pos.x + w / 2, top = pos.y - h / 2;

	exit = new Button(IMG->Add("credit_button"), IMG->Add("credit_button_cson"), { right + pos2.x ,top + pos2.y}, "", 70, 70, 0, [&]()->void { Off(); });
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
		bg->Render(pos, RT_ZERO, { 1,1 },0,0.2);
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
