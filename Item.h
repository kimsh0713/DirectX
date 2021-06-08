#pragma once
#include "Obj.h"
class Item :
    public Obj
{
public:
    Item(int type);

    Texture* img;
    V2 dir;

    // 1 �ӵ�, 2 ���, 3 ����, 4 ȸ��, 5 ����
    int type;

    // Obj��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void Enter(Col* p) override;
    virtual void Stay(Col* p) override;
    virtual void Exit(Col* p) override;
};

