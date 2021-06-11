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
    float Y;
    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

