#pragma once
#include "Obj.h"
class Item :
    public Obj
{
public:
    Item(int type);

    Texture* img;
    V2 dir;

    // 1 속도, 2 방어, 3 무적, 4 회복, 5 랜덤
    int type;

    // Obj을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void Enter(Col* p) override;
    virtual void Stay(Col* p) override;
    virtual void Exit(Col* p) override;
};

