#pragma once
#include "Scene.h"
class End :
    public Scene
{
public:
    End(int type);

    Texture* bg;
    Texture* game;
    Texture* clear;
    Texture* over;
    ScrollMap* map;

    Button* restart;
    Button* title;

    int type;

    // Scene��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

