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
		delete mVertex;
	if (nullptr != mShader)
		delete mShader;
}

void AsPolygon::Render(float interpolation)
{
	AS_UNUSED(interpolation);
	mShader->Use();
	mVertex->RenderSelf(GL_LINE_LOOP);
}