#include "DXUT.h"
#include "InputMgr.h"

bool InputMgr::Up(BYTE key)
{
    return !now[key] && prev[key];
}

bool InputMgr::Press(BYTE key)
{
    return now[key] && prev[key];
}

bool InputMgr::Down(BYTE key)
{
    return now[key] && !prev[key];
}

bool InputMgr::AnyKey()
{
    for (size_t i = 0; i < 256; i++)
        if (Down(i))
            return true;
    return false;
}

V2 InputMgr::GetMousePos()
{
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(DXUTGetHWND(), &pt);
    V2 pos = { float(pt.x),float(pt.y) };
    pos -= {float(WINX / 2 - CAM->pos.x), float(WINY / 2 - CAM->pos.y)};
    return pos;
}

void InputMgr::Update()
{
    memcpy(prev, now, sizeof(now));
    memset(now, 0, sizeof(now));

    for (size_t i = 0; i < 256; i++)
    {
        if (i == 21)
            continue;
        now[i] = false;
        if (GetAsyncKeyState(i))
            now[i] = true;
    }
}
