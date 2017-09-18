#include <iostream>

#include "AsWindow.h"

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

	AsPolygon * polygon = new AsPolygon("poly", mScene->mRoot);
	polygon->mColor = AsColor(1.0f, 0.0f, 0.0f, 1.0f);

	float pos[9] =
	{
	0.3f, 0.5f, 0.0f,
	0.1f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f
	};
	polygon->mVertex->LoadData(pos, FLAG_POSITION_ONLY, 3, nullptr, 0, GL_STATIC_DRAW);
	

	AsPolygon * polygon2 = new AsPolygon("poly2", mScene->mRoot);
	polygon2->mColor = AsColor(0.0f, 1.0f, 0.0f, 1.0f);

	float pos2[9] =
	{
		-0.3f, 0.5f, 0.0f,
		-0.1f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	polygon2->mVertex->LoadData(pos2, FLAG_POSITION_ONLY, 3, nullptr, 0, GL_STATIC_DRAW);
}

int main()
{
	MyWindow window(50, 50, 800, 600, "Test Window");

	window.exec();

	return 0;
}