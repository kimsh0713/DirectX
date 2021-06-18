#pragma once
#include "Scene.h"
class Ingame :
    public Scene
{
public:
    Ingame(int type);

    // UI
    Texture* Ui_base;
    Texture* Ui_score;
    Texture* Ui_stage;
    Texture* Ui_precent;
    Button* Ui_pause;
    Texture* Ui_abled_life;
    Texture* Ui_unabled_life;
    Texture* Ui_time;
    Texture* Ui_timer_tank;
    Texture* Ui_timer_bar;

    // OBJECT
    Obj* player;

    // TIMER
    int timer;
    Timer* playtime;

    float Y = 60;
    int type;
    int enemy_count = 3;
    
    static int stage;

    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

