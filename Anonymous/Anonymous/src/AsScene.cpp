#include "AsScene.h"

AsScene::AsScene(string name)
{
	mName = name;
	mRoot = new AsEmptyObject("__AsObjectRoot__", nullptr);
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
	mRoot->_Update(dt);
}

void AsScene::Render(float interpolation)
{
	mRoot->_Render(interpolation);
}

void AsScene::PrepareAndCompileShaders()
{
	mRoot->_PrepareAndCompileShaders();
}