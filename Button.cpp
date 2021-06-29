#include "DXUT.h"
#include "Button.h"

Button::Button(Texture* bg,Texture* bg2, V2 pos, const string& text, float w, float h, float depth, function<void()> func)
	:bg(bg), bg2(bg2), text(text), func(func), depth(depth), isOn(true)
{
	this->pos = pos;

	main_col = new Col(this, UI);

	W = w;
	H = h;
	b_pos = pos;


	OBJ->Add(this, "Button");
	b_pos = this->pos;
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
	title_button_Sound = SOUND->Add("button_click", L"button_click");
}

void Button::Update()
{
	main_col->Set(b_pos, W, H);
	if (!isOn)
	{
		r = 255;
		g = 255;
		b = 255;
	}
}

void Button::Render()
{
	if (isOn)
	{
		if(!ismouse)
			bg->Render(pos, RT_ZERO, { 1,1 }, 0, depth, D3DCOLOR_RGBA(r, g, b, 255));
		else
			bg2->Render(pos, RT_ZERO, { 1,1 }, 0, depth, D3DCOLOR_RGBA(r, g, b, 255));
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
			ismouse = true;
			//r = 155;
			//g = 155;
			//b = 155;	
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
				ismouse = false;
				func();
				if (SOUND->sound)
				{
					title_button_Sound->Copy();
				}
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
			ismouse = false;
			//r = 255;
			//g = 255;
			//b = 255;
			break;
		}
}
