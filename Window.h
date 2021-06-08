#pragma once
#include "Obj.h"
class Window :
    public Obj
{
public:
    Window(Texture* bg, V2 pos, float w, float h);

    Texture* bg;
    Button* exit;

    bool isOn;

    void On();
    void Off();

    // Obj을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void Enter(Col* p) override;
    virtual void Stay(Col* p) override;
    virtual void Exit(Col* p) override;
};

