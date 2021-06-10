#pragma once
#include "Scene.h"
class Ingame :
    public Scene
{
public:
    Ingame(int type);

    // UI
    Texture* Ui_base;
    Button* Ui_pause;

    //OBJECT
    Obj* player;

    float Y = 60;
    int type;
    int enemy_count = 3;

    // Scene��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
};

