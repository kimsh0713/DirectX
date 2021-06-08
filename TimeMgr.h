#pragma once
struct Timer
{
    Timer(float time) { Set(time); }
    ~Timer() { ; };

    void Set(float time) { set = cur = time; flag = false; }
    bool IsStop() { return !flag; }
    void Start() { flag = true; }

    void Update();

    float cur = 0, set = 0;
    bool flag = false;
};
class TimeMgr :
    public st<TimeMgr>
{
public:
    TimeMgr() { ; };
    ~TimeMgr();

    void Update();

    Timer* Create(float time);

    list<Timer*> l_timer;
};

#define TIME TimeMgr::G()