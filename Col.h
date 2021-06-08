#pragma once
#include "Obj.h"
class Obj;
class Col :
	public RECT
{
public:
	Col(Obj* p, Tag tag = TAG_BEGIN, int damage = 0);
	~Col();

	void Set(V2 pos, float w, float h);
	void Draw();
	RECT G() { return { left,top,right,bottom }; }

	LPD3DXLINE line;
	Obj* owner;
	V2 pos;
	Tag tag;
	int damage;
	bool flag = true;
	bool enter = false;
};

