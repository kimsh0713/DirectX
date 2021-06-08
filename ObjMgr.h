#pragma once
#include "Obj.h"
class ObjMgr :
	public st<ObjMgr>
{
public:
	ObjMgr();
	~ObjMgr();

	void Update();
	void Render();
	void Release();

	Obj* Add(Obj* p, const string& key);
	void Add(Col* p) { l_col.emplace_back(p); }
	Obj* Find(const string& key);

	void Clear();
	bool MapOut(Obj* p);

	list<Obj*> l_obj;
	list<Col*> l_col;
	bool layer[TAG_END][TAG_END];
};

#define OBJ ObjMgr::G()