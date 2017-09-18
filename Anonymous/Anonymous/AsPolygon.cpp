#include "AsPolygon.h"
#include <glad\glad.h>

AsPolygon::AsPolygon(string name, AsObject * parent)
	: AsObject(name, parent)
{
	mVertex = new AsVertexData();
	mColor = Color::_White;
	mShader = new AsShader();
}

AsPolygon::~AsPolygon()
{
	Release();
}

void AsPolygon::Release()
{
	if (nullptr != mVertex)
	{
		delete mVertex;
		mVertex = nullptr;
	}
	if (nullptr != mShader)
	{
		delete mShader;
		mVertex = nullptr;
	}
}

void AsPolygon::Render(float interpolation)
{
	AS_UNUSED(interpolation);
	mShader->Use();
	mShader->SetFloat4("_Color", mColor.r, mColor.g, mColor.b, mColor.a);
	mVertex->RenderSelf(GL_LINE_LOOP);
}

void AsPolygon::PrepareAndCompileShaders()
{
	// TODO
	// Transform matrix need be set
	mShader->PropareAndProcessShader();
}