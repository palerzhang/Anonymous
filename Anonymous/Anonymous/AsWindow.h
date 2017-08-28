#ifndef _ANONYMOUS_WINDOW_H_
#define _ANONYMOUS_WINDOW_H_

#include <string>
#include "GLFW/glfw3.h"

using namespace std;

enum AsWindowState
{
	WINDOW_STATE_RUNNING = 0,
	WINDOW_STATE_CLOSED,
	WINDOW_STATE_UNSTART
};

class AsWindow
{
	int mPosX;
	int mPosY;
	int mWidth;
	int mHeight;
	string mTitle;

	bool mResizable;
	bool mVisible;
	bool mFrameless;
	bool mFloating;
	bool mMaximized;

	bool mFullScreen;

	int TICKS_PER_SECOND;
	int MAX_FRAME_SKIP;
	float SKIP_TICKS;

	AsWindowState mState;

	GLFWwindow* mWindow;
	GLFWmonitor* mMonitor;

	static AsWindow * sInstanceHandleEvents;

	static void DispatchKeyboardEvents(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void DispatchMouseEvents(GLFWwindow* window, int button, int action, int mode);

	void Draw(float interpolation);

protected:
	virtual void KeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mode);
	virtual void MouseEvent(GLFWwindow* window, int button, int action, int mode);

	virtual GLFWwindow* CreateFullScreenWindow();
	virtual GLFWwindow* CreateDefaultWindow();

	virtual void OnClose();
	virtual void Update(float dt);
	virtual void MainLoop();

public:
	AsWindow(int posx, int posy, int w, int h, string title);
	~AsWindow();
	
	void SetPosition(int posx, int posy);
	void SetDimension(int w, int h);
	void SetTitle(string str);
	void SetResizable(bool resizable);
	void SetVisible(bool visible);
	void SetFrameless(bool frameless);
	void SetFloating(bool floating);
	void SetMaximized(bool miximized);
	void SetFullScreen(bool fullScreen);

	void CurrentInstanceHandleEvents() { sInstanceHandleEvents = this; }

	int width();
	int height();
	int x();
	int y();
	string title();
	bool resizable();
	bool visible();
	bool frameless();
	bool floating();
	bool maximized();
	bool fullScreen();
	AsWindowState state();

	int exec();
};

#endif