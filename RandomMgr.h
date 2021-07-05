#pragma once
class RandomMgr :
	public st<RandomMgr>
{
public:
	RandomMgr()
		:rd(), gen(rd()), r() {}

	~RandomMgr() { ; };

	int INT(int min, int max);
	V2 Vec2(V2 origin);

	void Reflex(V2* dir_out, V2 side);

	random_device rd;
	mt19937 gen;
	uniform_int_distribution<int> r;
};

#define RANDOM RandomMgr::G()