#pragma once
class Timer;
class CamMgr :
	public st<CamMgr>
{
public:
	CamMgr();
	~CamMgr() { ; };

	void Update();
	void Reset();
	void Apply();

	M pro, view;
	V2 pos, size;
	V3 scale;
};

#define CAM CamMgr::G()