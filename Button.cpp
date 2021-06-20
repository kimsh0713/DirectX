#include "DXUT.h"
#include "Button.h"

Button::Button(Texture* bg, V2 pos, const string& text, float w, float h, float depth, function<void()> func)
	:bg(bg), text(text), func(func), depth(depth), isOn(true)
{
	this->pos = pos;

	main_col = new Col(this, UI);

	W = w;
	H = h;
	b_pos = pos;


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
	b_pos = this->pos;
	main_col->Set(b_pos, W, H);
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
			r = 155;
			g = 155;
			b = 155;
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
			{
				r = 255;
				g = 255;
				b = 255;
				func();
			}
			break;
		}
}

void Button::Exit(Col* p)
{
	if (isOn)
		switch (p->tag)
		{
		case MOUSE:
			r = 255;
			g = 255;
			b = 255;
			break;
		}
}
