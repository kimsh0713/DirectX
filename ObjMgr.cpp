#include "DXUT.h"
#include "ObjMgr.h"

ObjMgr::ObjMgr()
	:layer
	{
	//   1,2,3,4,5,6,7,8
		{0,1,0,0,0,0,0,0},  // 1 UI
		{0,0,0,0,0,0,0,0},  // 2 MOUSE
		{0,0,0,0,0,1,1,1},  // 3 P
		{0,0,0,0,0,0,0,0},  // 4 PATK
		{0,0,0,1,0,0,0,0},  // 5 E
		{0,0,0,0,0,0,0,0},  // 6 EATK
		{0,0,0,0,0,0,0,0},  // 7 OBS
		{0,0,0,0,0,0,0,0},  // 8 ITEM
	}
{
}

ObjMgr::~ObjMgr()
{
	for (auto& i : l_obj)
	{
		i->Release();
		SAFE_DELETE(i);
	}
	l_obj.clear();
}

void ObjMgr::Update()
{
	for (auto& i = l_obj.begin(); i != l_obj.end(); ++i)
	{
		Obj* obj = (*i);
		if (obj->flag || MapOut(obj))
		{
			obj->Release();
			SAFE_DELETE(obj);
			i = l_obj.erase(i);
			if (i == l_obj.end())
				break;
		}
		else
			obj->Update();
	}
	for (auto& o : l_col)
	{
		for (auto& t : l_col)
		{
			if (!o) { l_col.remove(o); }
			else if (!o->flag || !t->flag) { ; }
			else if (layer[o->tag][t->tag])
			{
				RECT rt;
				Col* col = t;

				if (o->tag == UI)
					col = o;

				if (IntersectRect(&rt, &o->G(), &t->G()))
				{
					if (!col->enter)
					{
						col->enter = true;
						o->owner->Enter(t);
					}
					o->owner->Stay(t);
				}
				else
				{
					if (col->enter)
					{
						col->enter = false;
						o->owner->Exit(t);
					}
				}
			}
		}
	}
}

void ObjMgr::Render()
{
	for (auto& i : l_obj)
		i->Render();
}

void ObjMgr::Release()
{
	for (auto& i : l_obj)
		i->Release();
}

Obj* ObjMgr::Add(Obj* p, const string& key)
{
	if (p)
	{
		p->key = key;
		l_obj.emplace_back(p);
		p->Init();
		return p;
	}
	return nullptr;
}

Obj* ObjMgr::Find(const string& key)
{
	for (auto& i : l_obj)
		if (i->key == key)
			return i;
	return nullptr;
}

void ObjMgr::Clear()
{
	for (auto& i : l_obj)
		i->flag = true;
}

bool ObjMgr::MapOut(Obj* p)
{
	if (p)
		return (p->pos.x < 0 || p->pos.x > WINX ||
			p->pos.y < 0 || p->pos.y > WINY);
	return false;
}
