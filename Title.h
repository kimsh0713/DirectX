#pragma once
#include "Scene.h"
class Title :
    public Scene
{
public:
    Title(int type);

    Texture* bg;
    Texture* boy;
    Texture* clock;
    Texture* a;

    vector<Texture*> sh_anim;
    vector<Texture*> eb_anim;
    Timer* delay;
    int index = 0;

    Button* start;
    Button* credit;
    Button* howto;
    Button* exit;
    Button* setting;

    Window* win_credit;
    ScrollMap* map;

    int type;
    int r = 255, g = 255, b = 255;

    bool isDown = true;
    bool isDown2 = true;
    float Y;
    float Y2;
    float i = 0;

    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

