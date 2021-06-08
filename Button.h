#pragma once
#include "Obj.h"
class Button :
    public Obj
{
public:
    Button(Texture* bg, V2 pos, const string& text, float w, float h, float depth, function<void()> func);

    Texture* bg;
    string text;
    function<void()> func;

    int r = 255, g = 255, b = 255;

    float depth;

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

