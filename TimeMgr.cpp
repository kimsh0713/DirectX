#include "DXUT.h"
#include "TimeMgr.h"

TimeMgr::~TimeMgr()
{
	for (auto& i : l_timer)
		SAFE_DELETE(i);
	l_timer.clear();
}

void TimeMgr::Update()
{
	for (auto& i : l_timer)
	{
		if (!i) { l_timer.remove(i); SAFE_DELETE(i); }
		else i->Update();
	}
}

Timer* TimeMgr::Create(float time)
{
	Timer* temp = new Timer(time);
	l_timer.emplace_back(temp);
	return temp;
}

void Timer::Update()
{
	if (flag)
	{
		cur -= DT;
		if (cur <= 0)
		{
			cur = set;
			flag = false;
		}
	}
}
