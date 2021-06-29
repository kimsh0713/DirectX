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
    
    Texture* sound_on;
    Texture* sound_mute;

    vector<Texture*> sh_anim;
    vector<Texture*> eb_anim;
    Timer* delay;
    int index = 0;

    Button* start;
    Button* credit;
    Button* howto;
    Button* exit;
    Button* setting;

    Button* sound_button;
    Button* sound_button_mute;

    Sound* title_button_cSound;

    Window* win_credit;
    Window* win_howto;
    Window* win_setting;
    ScrollMap* map;

    int type;
    int r = 255, g = 255, b = 255;

    bool isDown = true;
    bool isDown2 = true;
    bool iswindow = false;
    float Y;
    float Y2;
    float i = 0;

    // Scene��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

