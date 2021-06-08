#pragma once
#include "Scene.h"
class Ingame :
    public Scene
{
public:
    Ingame(int type);

    Texture* bg;
    ScrollMap* map;
    Texture* Img;
    Texture* BackGround;

    int type;
    int enemy_count = 4;

    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

