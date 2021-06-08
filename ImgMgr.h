#pragma once
struct Texture
{
	LPDIRECT3DTEXTURE9 p;
	D3DXIMAGE_INFO info;
	Texture(LPDIRECT3DTEXTURE9 p, D3DXIMAGE_INFO info)
		:p(p), info(info) {}

	void CenterRender(V2 pos, float rot = 0, V2 size = V2(1, 1), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void Render(V2 pos = CENTER, RECT rt = RT_ZERO, V2 size = { 1,1 }, float rot = 0, float depth = 1, D3DXCOLOR color = D3DCOLOR_RGBA(255, 255, 255, 255), bool center = true);
	void Release() { SAFE_RELEASE(p); }
};
class ImgMgr :
	public st<ImgMgr>
{
public:
	ImgMgr();
	~ImgMgr();

	Texture* Add(const string& key);

	void Begin();
	void CenterRender(Texture* p, V2 pos, float rot = 0, V2 size = V2(1, 1), D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void Render(Texture* p, V2 pos = CENTER, RECT rt = RT_ZERO, V2 size = { 1,1 }, float rot = 0, float depth = 1, D3DXCOLOR color = D3DCOLOR_RGBA(255, 255, 255, 255), bool center = true);
	void Write(const string& str, V2 pos = CENTER, float size = 50, D3DXCOLOR color = D3DCOLOR_RGBA(255, 255, 255, 255), bool center = true);
	void End();

	void Lost();
	void Reset();
	Texture* ReLoad(const string& key);

	LPD3DXSPRITE sprite;
	LPD3DXFONT font;
	map<string, Texture*>textures;
};

#define IMG ImgMgr::G()