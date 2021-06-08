#pragma once
class InputMgr :
    public st<InputMgr>
{
public:
    InputMgr() { ; };
    ~InputMgr() { ; };

    bool Up(BYTE key);
    bool Press(BYTE key);
    bool Down(BYTE key);
    bool AnyKey();

    V2 GetMousePos();

    void Update();

    bool now[256] = { 0, };
    bool prev[256] = { 0, };
};

#define INPUT InputMgr::G()