#pragma once
#include "Scene.h"
class WaitTitle :
    public Scene
{
    Texture* bg;
    Texture* boy;
    Texture* title;
    Texture* press;
    Texture* clock;

    bool isDown = true;
    bool isDown2 = true;
    float Y;
    float Y2;
    float i = 0;

    Sound* Back_Ground_music;

    // Scene��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

