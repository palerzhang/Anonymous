#include "AsScene.h"

AsScene::AsScene(string name)
{
	mName = name;
	mRoot = new AsEmptyObject(nullptr, "__AsObjectRoot__");
}

AsScene::~AsScene()
{
	Release();
}

void AsScene::Release()
{
	if (nullptr != mRoot)
		delete mRoot;
}

void AsScene::Update(float dt)
{
	//mCamera.Update(dt);
	mRoot->Update(dt);
}

void AsScene::Render(float interpolation)
{
	mRoot->Render(interpolation);
}