#include "DXUT.h"
#include "RandomMgr.h"

int RandomMgr::INT(int min, int max)
{
	r = uniform_int_distribution<int>(min, max);
	return r(gen);
}

V2 RandomMgr::Vec2(V2 origin)
{
	V2 dir;
	dir = { float(RANDOM->INT(L + 1, R - 1) - origin.x),float(RANDOM->INT(T + 1, B - 1) - origin.y) };
	D3DXVec2Normalize(&dir, &dir);
	return dir;
}

void RandomMgr::Reflex(V2* dir_out, V2 side)
{
	(*dir_out) = (*dir_out) + 2 * side * D3DXVec2Dot(&-(*dir_out), &side);
}