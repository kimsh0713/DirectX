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
    // Scene��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

