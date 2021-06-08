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

    // Scene��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

