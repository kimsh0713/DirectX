﻿#pragma once
#include "Obj.h"
class Enemy :
    public Obj
{
public:
    Enemy(int type);

    vector<Effect*> fxs;
    Texture* img;
    Timer* timer;
    Timer* during;
    V2 size;
    V2 dir;

    float front;

    float cool;
    float rot;
    float t = 0;
    float t2 = 0;
    float t3 = 0;
    int type;
    //int enemytype = 1;
    int spin_force;

    vector<Texture*> turtle;

    vector<int> E_type = vector<int>
    {
        1,
        1,
        1,
    };

    vector<V2> sizes = vector<V2>
    {
        {0.5f,0.5f},
        {1,1},
        {3.5,3.5},
        {4,4},
        {6,6},
        {12,6},
        {17,16},
        {7,7},
    };

    void Flash();
    void Rush();
    void Shot(int shots);

    // Obj을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void Enter(Col* p) override;
    virtual void Stay(Col* p) override;
    virtual void Exit(Col* p) override;
};

