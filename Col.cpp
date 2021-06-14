#include "DXUT.h"
#include "Col.h"

Col::Col(Obj* p, Tag tag, int damage)
	:owner(p), tag(tag), damage(damage)
{
	D3DXCreateLine(DEVICE, &line);
	line->SetAntialias(true);
	line->SetWidth(1);
	OBJ->Add(this);
}

Col::~Col()
{
	OBJ->l_col.remove(this);
	line->Release();
}

void Col::Set(V2 pos, float w, float h)
{
	this->pos = pos;
	left = pos.x - w / 2;
	right = pos.x + w / 2;
	top = pos.y - h / 2;
	bottom = pos.y + h / 2;
}

void Col::SetPos(V2 vPos)
{
	this->pos = pos;
}

void Col::Draw()
{
	if (ColDraw)
	{
		V2* vs = new V2[5];
		vs[0] = { float(left),float(top) };
		vs[1] = { float(right),float(top) };
		vs[2] = { float(right),float(bottom) };
		vs[3] = { float(left),float(bottom) };
		vs[4] = { float(left),float(top) };

		line->Begin();
		line->Draw(vs, 5, D3DCOLOR_RGBA(80, 80, 80, 255));
		line->End();

		SAFE_DELETE_ARRAY(vs);
	}
}
