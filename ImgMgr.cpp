#include "DXUT.h"
#include "ImgMgr.h"

void Texture::CenterRender(V2 pos, float rot, V2 size, D3DCOLOR color)
{
	IMG->CenterRender(this, pos, rot, size, color);
}

void Texture::Render(V2 pos, RECT rt, V2 size, float rot, float depth, D3DXCOLOR color, bool center)
{
	IMG->Render(this, pos, rt, size, rot, depth, color, center);
}

ImgMgr::ImgMgr()
	:sprite(nullptr), font(nullptr)
{
	D3DXCreateSprite(DEVICE, &sprite);
}

ImgMgr::~ImgMgr()
{
	for (auto& iter : textures)
	{
		iter.second->Release();
		SAFE_DELETE(iter.second);
	}
	textures.clear();
	sprite->Release();
}

Texture* ImgMgr::Add(const string& key)
{
	auto f = textures.find(key);
	if (f == textures.end())
	{
		LPDIRECT3DTEXTURE9 p;
		D3DXIMAGE_INFO info;

		char str[256];
		sprintf(str, "./Resource/image/%s.png", key.c_str());

		if (D3DXCreateTextureFromFileExA(DEVICE, str, -2, -2, 0, 0, (D3DFORMAT)0, (D3DPOOL)1, -1, -1, 0, &info, nullptr, &p) == S_OK)
		{
			Texture* temp = new Texture(p, info);
			textures[key] = temp;
			return temp;
		}
		return nullptr;
	}
	return f->second;
}

void ImgMgr::Begin()
{
	sprite->Begin(1 << 4 | 1 << 2 | 1 << 6);
}

void ImgMgr::CenterRender(Texture* p, V2 pos, float rot, V2 size, D3DCOLOR color)
{
	if (p)
	{
		D3DXMATRIXA16 mat;
		V2 CenterPos = V2(p->info.Width / 2, p->info.Height / 2);
		pos -= CenterPos;

		D3DXMatrixTransformation2D(&mat, &CenterPos, 0, &size, &CenterPos, rot, &pos);

		sprite->SetTransform(&mat);
		sprite->Draw(p->p, nullptr, nullptr, nullptr, color);
	}
}

void ImgMgr::Render(Texture* p, V2 pos, RECT rt, V2 size, float rot, float depth, D3DXCOLOR color, bool center)
{
	if (p)
	{
		M m;
		V2 cpos = { 0,0 };
		RECT* prt = &rt;

		if (rt.right == 0 && rt.left == 0 && rt.bottom == 0 && rt.top == 0)
			prt = nullptr;

		if (center)
			cpos = { float(p->info.Width / 2), float(p->info.Height / 2) };

		pos -= cpos;
		D3DXMatrixTransformation2D(&m, &cpos, 0, &size, &cpos, rot, &pos);
		m._43 = depth;
		sprite->SetTransform(&m);
		sprite->Draw(p->p, prt, nullptr, nullptr, color);
	}
}

void ImgMgr::Write(const string& str, V2 pos, float size, D3DXCOLOR color, bool center)
{
	M m;
	V2 v = pos;

	if (center)
		v -= {float(size* (str.size() * 0.25)), float(size / 2)};

	D3DXMatrixTranslation(&m, v.x, v.y, 0);
	sprite->SetTransform(&m);
	D3DXCreateFontA(DEVICE, size, 0, center ? 0 : 10, 1, 0, 129, 0, 0, 0, "Fixedsys", &font);
	font->DrawTextA(sprite, str.c_str(), str.size(), nullptr, DT_NOCLIP, color);
	SAFE_RELEASE(font);
}

void ImgMgr::End()
{
	sprite->End();
}

void ImgMgr::Lost()
{
	sprite->OnLostDevice();
}

void ImgMgr::Reset()
{
	sprite->OnResetDevice();
}

Texture* ImgMgr::ReLoad(const string& key)
{
	auto find = textures.find(key);
	if (find != textures.end())
	{
		find->second->Release();
		SAFE_DELETE(find->second);
		textures.erase(find);
	}
	return IMG->Add(key);
}