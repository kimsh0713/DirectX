#pragma once
#include "Obj.h"
class Enemy :
    public Obj
{
public:
    Enemy(int type);

    vector<Effect*> fxs;
    Texture* img;
    Texture* img_back;
    Timer* timer;
    float during = 0;
    int back_alpha = 0;
    Timer* dummy = 0;
    V2 size;
    V2 dir;

    float front;

    int motion = 0;

    float cool;
    float rot;
    float t = 0;
    float t2 = 0;
    float t3 = 0;
    float t4 = 0;
    int type;
    //int enemytype = 1;
    int spin_force;

    vector<Texture*> turtle;

    vector<int> E_type = vector<int>
    {
        1,
        1,
        0,
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
        {16,8},
    };

    // Obj을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void Enter(Col* p) override;
    virtual void Stay(Col* p) override;
    virtual void Exit(Col* p) override;
};

