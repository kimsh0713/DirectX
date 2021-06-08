#pragma once
class HotKey :
    public st<HotKey>
{
public:
    HotKey();
    ~HotKey() { ; };

    void Reset() { player = OBJ->Find("player"); };

    void F1();
    void F2();
    void F3();
    void F4();
    void F5();
    void F6();

    Obj* player;
};

#define HOT HotKey::G()