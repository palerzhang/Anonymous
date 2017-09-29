#include "AsImage.h"

AsImage::AsImage(string name, AsObject * parent)
	: AsObject(name, parent)
{
	mVertex = new AsVertexData();
	mColor = Color::_White;
	mTexture = new AsTexture2D();
	mShader = new AsShader();

	mWidth = 1.0f;
	mHeight = 1.0f;

	float data[] =
	{	// position			// uv
		0.5f, 0.5f, 0.0f,  1.0f, 1.0f,   
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f,   
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,  
		-0.5f, 0.5f, 0.0f,  0.0f, 1.0f
	};

	mVertex->LoadData(data, FLAG_POSITION_UV, 4, nullptr, 0, GL_STATIC_DRAW);

	mShader->SetShaderFile("default_image", "default_image");
}

AsImage::~AsImage()
{
	Release();
}

void AsImage::Release()
{
	if (nullptr != mVertex)
	{
		delete mVertex;
		mVertex = nullptr;
	}
	if (nullptr != mTexture)
	{
		delete mTexture;
		mTexture = nullptr;
	}
	if (nullptr != mShader)
	{
		delete mShader;
		mShader = nullptr;
	}
}

void AsImage::Render(float interpolation)
{
	AS_UNUSED(interpolation);
	mTexture->ActiveTexture();
	mShader->Use();
	mShader->SetFloat4("_Color", mColor.r, mColor.g, mColor.b, mColor.a);
	mVertex->RenderSelf(GL_POLYGON);
}

void AsImage::PrepareAndCompileShaders()
{
	// TODO
	// Transform matrix need be set
	mShader->SetInt("mainTexture", 0);
	mShader->PropareAndProcessShader();
}