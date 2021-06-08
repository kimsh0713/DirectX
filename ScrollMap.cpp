#include "DXUT.h"
#include "ScrollMap.h"

void ScrollMap::Update(float speed)
{
	scroll -= speed * DT;
}

void ScrollMap::Render()
{
	float gap = (int)scroll % bg->info.Width;
	bg->Render({ (WINX / 2 + gap) - bg->info.Width,WINY / 2 }, RT_ZERO, { 1,1.0546875f });
	bg->Render({ (WINX / 2 + gap),WINY / 2 }, RT_ZERO, { 1,1.0546875f });
}
