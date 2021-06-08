#include "DXUT.h"
#include "Button.h"

Button::Button(Texture* bg, V2 pos, const string& text, float w, float h, float depth, function<void()> func)
	:bg(bg), text(text), func(func), depth(depth), isOn(true)
{
	this->pos = pos;

	main_col = new Col(this, UI);
	main_col->Set(pos, w, h);

	OBJ->Add(this, "Button");
}

void Button::On()
{
	isOn = true;
	main_col->flag = true;
}

void Button::Off()
{
	isOn = false;
	main_col->flag = false;
}

void Button::Init()
{
}

void Button::Update()
{
}

void Button::Render()
{
	if (isOn)
	{
		bg->Render(pos, RT_ZERO, { 1,1 }, 0, depth, D3DCOLOR_RGBA(r, g, b, 255));
		IMG->Write(text, pos);
		main_col->Draw();
	}
}

void Button::Release()
{
	SAFE_DELETE(main_col);
}

void Button::Enter(Col* p)
{
	if (isOn)
		switch (p->tag)
		{
		case MOUSE:
			r -= 100;
			g -= 100;
			b -= 100;
			break;
		}
}

void Button::Stay(Col* p)
{
	if (isOn)
		switch (p->tag)
		{
		case MOUSE:
			if (INPUT->Down(VK_LBUTTON))
				func();
			break;
		}
}

void Button::Exit(Col* p)
{
	if (isOn)
		switch (p->tag)
		{
		case MOUSE:
			r += 100;
			g += 100;
			b += 100;
			break;
		}
}
