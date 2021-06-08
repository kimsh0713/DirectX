#pragma once
#include "Col.h"
class Obj
{
public:
	Obj() { ; };
	virtual ~Obj() { ; };

	Col* main_col = nullptr;
	V2 pos = CENTER;
	string key = "";
	int hp = 0;
	int max_hp = 0;
	float speed = 0;
	bool flag = false;

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
	virtual void Enter(Col* p) PURE;
	virtual void Stay(Col* p) PURE;
	virtual void Exit(Col* p) PURE;
};

