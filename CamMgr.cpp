#include "DXUT.h"
#include "CamMgr.h"

CamMgr::CamMgr()
{
	Reset();

	D3DXMatrixOrthoLH(&pro, size.x, -size.y, 0, 1);
}

void CamMgr::Update()
{
	view =
	{
		scale.x,0,0,0,
		0,scale.y,0,0,
		0,0,scale.z,0,
		-pos.x,-pos.y,0,1,
	};
}

void CamMgr::Reset()
{
	pos = CENTER;
	size = { WINX,WINY };
	scale = { 1,1,1 };
}

void CamMgr::Apply()
{
	DEVICE->SetTransform(D3DTS_VIEW, &view);
	DEVICE->SetTransform(D3DTS_PROJECTION, &pro);
}
