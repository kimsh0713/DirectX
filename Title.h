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

    Texture* sound_on;
    Texture* sound_mute;

    Texture* music_on;
    Texture* music_mute;

    Button* sound_button;
    Button* music_button;

    Sound* title_button_cSound;
    Sound* Back_Ground_music;

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

    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

