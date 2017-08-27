#ifndef _ANONYMOUS_WINDOW_H_
#define _ANONYMOUS_WINDOW_H_

#include <string>
using namespace std;

class AsWindow
{
	float mPosX;
	float mPosY;
	float mWidth;
	float mHeight;
	string mTitle;

	bool mResizable;
	bool mVisible;
	bool mFrameless;
	bool mFloating;
	bool mMaximized;

	bool nFullScreen;

public:
	AsWindow(float posx, float posy, float w, float h, string title);
	~AsWindow();
	
	inline void SetPosition(float posx, float posy);
	inline void SetDimension(float w, float h);
	inline void SetTitle(string str);
	inline void SetResizable(bool resizable);
	inline void SetVisible(bool visible);
	inline void SetFrameless(bool frameless);
	inline void SetFloating(bool floating);
	inline void SetMaximized(bool miximized);
	inline void SetFullScreen(bool fullScreen);

	inline float width();
	inline float height();
	inline float x();
	inline float y();
	inline string title();
	inline bool resizable();
	inline bool visible();
	inline bool frameless();
	inline bool floating();
	inline bool maximized();
	inline bool fullScreen();
};

#endif