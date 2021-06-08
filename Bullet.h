#pragma once
#include "Obj.h"
class Bullet :
    public Obj
{
public:
    Bullet(int type, V2 dir);

    Texture* img;
    vector<Effect*> fxs;
    Timer* delay;
    V2 dir;

    int type;
    float speed;

    // Obj을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void Enter(Col* p) override;
    virtual void Stay(Col* p) override;
    virtual void Exit(Col* p) override;
};

