#include "DXUT.h"
#include "MainGame.h"

void MainGame::Init()
{
	SCENE->Add(new Title(1), "intro");
	SCENE->Add(new Title(2), "title");
	SCENE->Add(new WaitTitle, "WaitTitel");
	SCENE->Add(new Ingame(1), "stage1");
	SCENE->Add(new Ingame(2), "stage2");
	SCENE->Add(new Ingame(3), "stage3");
	SCENE->Add(new End(1), "clear");
	SCENE->Add(new End(2), "fail");
	SCENE->Set("WaitTitel");
}

void MainGame::Update()
{
	INPUT->Update();
	TIME->Update();
	CAM->Update();
	SCENE->Update();
	OBJ->Update();
}

void MainGame::Render()
{
	CAM->Apply();

	IMG->Begin();
	SCENE->Render();
	OBJ->Render();
	IMG->End();
}

void MainGame::Release()
{
	CamMgr::D();
	ImgMgr::D();
	ObjMgr::D();
	HotKey::D();
	TimeMgr::D();
	SceneMgr::D();
	SoundMgr::D();
	InputMgr::D();
	RandomMgr::D();
}

void MainGame::Lost()
{
	IMG->Lost();
}

void MainGame::Reset()
{
	IMG->Reset();
}
