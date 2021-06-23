#pragma once
#include "Obj.h"
class Player :
    public Obj
{
public:
    Texture* img;
    // stage 1
    Texture* bg;
    Texture* bg2;

    Texture* Over;
    Timer* during;
    Obj* boss;
    V2 start;
    V2 last;

    D3DXCOLOR bg_color[CELLSIZE_X * CELLSIZE_Y];

    enum class KeyState
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
    };

    KeyState key;

    static int cell[CELLSIZE_X][CELLSIZE_Y];
    static float coloring_per;
    static bool isHurt;

    int total_cell = CELLSIZE_X * CELLSIZE_Y;
    int coloring_cells = 0;
    int temp = 0;
    int spin_force = 0;
    int def = 0;
    int num = 0;

    float rot;

    bool draw_mode = false;
    bool no_damage = false;

    void InputKey();
    void Hurt();
    void SetUp();
    void DrawLine();
    // 0 normal, 1 filled, 2 cancel
    void DrawArea(int draw_flag = 0);
    bool FloodFill(V2 pos, int target, int change);
    void AutoFill();
    void AddItem();
    void NoDamage();
    bool Near(KeyState dir, int target);
    int  Current();
    void reset();

    // Obj을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Release() override;
    virtual void Enter(Col* p) override;
    virtual void Stay(Col* p) override;
    virtual void Exit(Col* p) override;
};

