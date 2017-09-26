#ifndef _ANONYMOUS_WINDOW_H_
#define _ANONYMOUS_WINDOW_H_

#include <string>
#include <glad/glad.h>
#include "GLFW\glfw3.h"
#include "AsScene.h"
#include "AsInputEvent.h"
#include <Foundation\AsColor.h>

using namespace std;

/*
\ Window State
\	WINDOW_STATE_RUNNING : This window is running
\	WINDOW_STATE_CLOSED	: This window is closed
\	WINDOW_STATE_UNSTART : This window is not started
*/
enum AsWindowState
{
	WINDOW_STATE_RUNNING = 0,
	WINDOW_STATE_CLOSED,
	WINDOW_STATE_UNSTART
};

/*
\ Window State
\	WINDOW_FLAG_RESIZABLE : window is resizable
\	WINDOW_FLAG_VISIBLE : window is visible
\	WINDOW_FLAG_FRAMELESS : window is frameless
\	WINDOW_FLAG_FLOATING : window is floating
\	WINDOW_FLAG_MAXIMIZED : window is maximized
\	WINDOW_FLAG_FULLSCREEN : window is full-screen
*/
enum AsWindowFlag
{
	WINDOW_FLAG_RESIZABLE = 0,
	WINDOW_FLAG_VISIBLE,
	WINDOW_FLAG_FRAMELESS,
	WINDOW_FLAG_FLOATING,
	WINDOW_FLAG_MAXIMIZED,
	WINDOW_FLAG_FULLSCREEN
};

/*
\ Window
*/
class AsWindow
{
	/*
	\ Position of window's left-top point
	\ Note that in full-screen mode, the position will be ignored
	*/
	int mPosX;
	int mPosY;
	/*
	\ Window size
	\ Note that in full-screen mode, the size will be ignored
	*/
	int mWidth;
	int mHeight;
	/*
	\ Title of the window
	*/
	string mTitle;
	/*
	\ Backgroud color
	*/
	AsColor mBackground;
	/*
	\ Flags of window
	*/
	bool mResizable;
	bool mVisible;
	bool mFrameless;
	bool mFloating;
	bool mMaximized;
	bool mFullScreen;
	/*
	\ Time counter for main loop
	*/
	int TICKS_PER_SECOND;
	int MAX_FRAME_SKIP;
	float SKIP_TICKS;
	/*
	\ Window state
	*/
	AsWindowState mState;
	/*
	\ glfw window and monitor
	*/
	GLFWwindow* mWindow;
	GLFWmonitor* mMonitor;
	/*
	\ The window that handles events from mouse, keyboard and other 
	*/
	static AsWindow * sInstanceHandleEvents;
	/*
	\ Dispatch events to the window that handles event
	\ See @sInstanceHandleEvents
	*/
	static void DispatchKeyboardEvents(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void DispatchMouseEvents(GLFWwindow* window, int button, int action, int mode);
	static void DispatchResizeEvents(GLFWwindow* window, int width, int height);
	/*
	\ Render this window
	*/
	void Render(float interpolation);
	/*
	\ Initialize window environment
	*/
	void InitWindowEnvironment();

protected:
	/*
	\ Events handler, that can be override
	*/
	virtual void KeyboardEvent(AsKeyCode key, AsKeyAction action, AsModifierCode mod);
	virtual void MouseEvent(AsMouseCode button, AsMouseAction action, AsModifierCode mod);
	virtual void ResizeEvent(int width, int height);
	/*
	\ Window creation
	\ that can be override
	*/
	virtual GLFWwindow* CreateFullScreenWindow();
	virtual GLFWwindow* CreateDefaultWindow();
	/*
	\ When the window should be closed
	*/
	virtual void OnClose();
	/*
	\ Update window
	*/
	virtual void Update(float dt);
	/*
	\ Main game loop
	*/
	virtual void MainLoop();
	/*
	\ Custom construct scene in this function
	\ Inherit this class and override this function
	*/
	virtual void ConstructScene() = 0;
	/*
	\ Compile all shaders
	*/
	virtual void PrepareAndCompileShaders();

public:
	/*
	\ Scene that this window contains
	*/
	AsScene* mScene;
	/*
	\ Constructor and deconstructor
	*/
	AsWindow(int posx, int posy, int w, int h, const string & title);
	~AsWindow();
	/*
	\ Set position of the window's left top cornor
	\ This works only before running the window
	*/
	void SetPosition(int posx, int posy);
	/*
	\ Set the dimension of the window
	\ This works only before running the window
	*/
	void SetDimension(int w, int h);
	/*
	\ Set the title of window
	\ This works only before running the window
	*/
	void SetTitle(string str);
	/*
	\ Set and get window flags
	*/
	void SetWindowFlag(AsWindowFlag flag, bool enable);
	bool GetWindowFlag(AsWindowFlag flag);
	/*
	\ Set window background color
	*/
	inline void SetBackground(const AsColor & color)
	{
		mBackground = color;
	}
	/*
	\ Set this window as the event handler
	*/
	void CurrentInstanceHandleEvents() { sInstanceHandleEvents = this; }
	/*
	\ Get attributes of window
	*/
	int width();
	int height();
	int x();
	int y();
	string title();
	AsWindowState state();
	/*
	\ Execution of the window
	*/
	int exec();
};

#endif