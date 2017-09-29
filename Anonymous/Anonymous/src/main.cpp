#include <iostream>

#include "AsWindow.h"
#include "AsImage.h"

class MyWindow : public AsWindow
{
public:
	MyWindow(int x, int y, int w, int h, const string & title)
		: AsWindow(x, y, w, h, title){}
protected:
	void ConstructScene() override;
};

void MyWindow::ConstructScene()
{
	mScene = new AsScene("Scene0");

	AsImage * image = new AsImage("image", mScene->mRoot);
	image->mColor.a = 0.0f;

	image->mTexture->mFile = "wall.jpg";
	image->mTexture->mWrapMode = AS_REPEAT;
	image->mTexture->mMagnifyFilter = AS_NEAREST;
	image->mTexture->mMinifyFilter = AS_NEAREST;
	image->mTexture->mTextureMode = AS_RGBA;

	image->mTexture->GenerateTexture2D();

	/*AsPolygon * polygon = new AsPolygon("poly", mScene->mRoot);
	polygon->mColor = AsColor(0.2f, 0.6f, 0.8f, 1.0f);

	float pos[] =
	{
	0.3f, 0.5f, 0.0f,
	0.1f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f
	};
	polygon->mVertex->LoadData(pos, FLAG_POSITION_ONLY, 3, nullptr, 0, GL_STATIC_DRAW);
	
	AsPolygon * polygon2 = new AsPolygon("poly2", mScene->mRoot);
	polygon2->mColor = AsColor(0.7f, 1.0f, 0.3f, 1.0f);

	float pos2[] =
	{
		-0.1f, 0.5f, 0.0f,
		-0.1f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};
	polygon2->mVertex->LoadData(pos2, FLAG_POSITION_ONLY, 4, nullptr, 0, GL_STATIC_DRAW);*/
}

int main()
{
	MyWindow window(50, 50, 800, 600, "Test Window");
	window.SetBackground(AsColor(0.4f, 0.3f, 0.2f, 1.0f));

	window.exec();

	return 0;
}