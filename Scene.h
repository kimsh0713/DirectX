#pragma once
class Scene
{
public:
	Scene() { ; };
	virtual ~Scene() { ; };

	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
};

