#include "AsWindow.h"

/*
\ Version 1.0.0
\ draw a rotatable triangle
*/

AsWindow * AsWindow::sInstanceHandleEvents = nullptr;

void AsWindow::DispatchKeyboardEvents(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (AsWindow::sInstanceHandleEvents)
		AsWindow::sInstanceHandleEvents->KeyboardEvent(window, key, scancode, action, mode);
}

void AsWindow::DispatchMouseEvents(GLFWwindow* window, int button, int action, int mode)
{
	if (AsWindow::sInstanceHandleEvents)
		AsWindow::sInstanceHandleEvents->MouseEvent(window, button, action, mode);
}

void AsWindow::Draw(float interpolation)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.0f, 0.5f, 0.0f);
	glEnd();

	glfwSwapBuffers(mWindow);
}

GLFWwindow* AsWindow::CreateFullScreenWindow()
{
	mMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(mMonitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	mWidth = mode->width;
	mHeight = mode->height;

	return glfwCreateWindow(mode->width, mode->height, mTitle.c_str(), mMonitor, nullptr);
}

GLFWwindow* AsWindow::CreateDefaultWindow()
{
	return glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
}

void AsWindow::KeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void AsWindow::MouseEvent(GLFWwindow* window, int button, int action, int mode)
{
	// TODO
}

void AsWindow::OnClose()
{
	if (mState != WINDOW_STATE_CLOSED)
	{
		glfwSetWindowShouldClose(mWindow, GL_TRUE);
		glfwTerminate();
		mState = WINDOW_STATE_CLOSED;
		if (this != AsWindow::sInstanceHandleEvents)
			AsWindow::sInstanceHandleEvents = nullptr;
	}
}

void AsWindow::Update(float dt)
{
}

void AsWindow::MainLoop()
{
	double next_game_tick = glfwGetTime();
	int loops;
	float interpolation;
	float dt = 1.0f / TICKS_PER_SECOND;

	while (!glfwWindowShouldClose(mWindow))
	{
		glfwPollEvents();
		loops = 0;
		while (glfwGetTime() > next_game_tick && loops < MAX_FRAME_SKIP)
		{
			Update(dt);
			next_game_tick += SKIP_TICKS;
			loops++;
		}
		interpolation = float(glfwGetTime() + SKIP_TICKS - next_game_tick) / float(SKIP_TICKS);
		Draw(interpolation);
	}
}

AsWindow::AsWindow(int posx, int posy, int w, int h, string title)
{
	mPosX = posx;
	mPosY = posy;
	mWidth = w;
	mHeight = h;
	mTitle = title;

	mResizable = true;
	mVisible = true;
	mFrameless = false;
	mFloating = false;
	mMaximized = false;
	mFullScreen = false;

	mState = WINDOW_STATE_UNSTART;

	TICKS_PER_SECOND = 25;
	SKIP_TICKS = 1.0f / TICKS_PER_SECOND;
	MAX_FRAME_SKIP = 5;
}

AsWindow::~AsWindow()
{
	OnClose();
}

void AsWindow::SetPosition(int posx, int posy)
{
	mPosX = posx;
	mPosY = posy;
	if (nullptr != mWindow) glfwSetWindowPos(mWindow, mPosX, mPosY);
}

void AsWindow::SetDimension(int w, int h)
{
	mWidth = w;
	mHeight = h;
	if (nullptr != mWindow) glfwSetWindowSize(mWindow, mWidth, mHeight);
}

void AsWindow::SetTitle(string str)
{
	mTitle = str;
}

void AsWindow::SetResizable(bool resizable)
{
	mResizable = resizable;
}

void AsWindow::SetVisible(bool visible)
{
	mVisible = visible;
}

void AsWindow::SetFrameless(bool frameless)
{
	mFrameless = frameless;
}

void AsWindow::SetFloating(bool floating)
{
	mFloating = floating;
}

void AsWindow::SetMaximized(bool miximized)
{
	mMaximized = miximized;
}

void AsWindow::SetFullScreen(bool fullScreen)
{
	mFullScreen = fullScreen;

	if (nullptr == mWindow || nullptr != mMonitor)
		return;

	if (mFullScreen)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(mMonitor);
		glfwSetWindowMonitor(mWindow, mMonitor, mPosX, mPosY, mWidth, mHeight, mode->refreshRate);
	}
	else
	{
		glfwSetWindowMonitor(mWindow, nullptr, mPosX, mPosY, mWidth, mHeight, 0);
	}
}

int AsWindow::width()
{
	return mWidth;
}

int AsWindow::height()
{
	return mHeight;
}

int AsWindow::x()
{
	return mPosX;
}

int AsWindow::y()
{
	return mPosY;
}

string AsWindow::title()
{
	return mTitle;
}

bool AsWindow::resizable()
{
	return mResizable; 
}

bool AsWindow::visible()
{
	return mVisible;
}

bool AsWindow::frameless()
{
	return mFrameless;
}

bool AsWindow::floating()
{
	return mFloating;
}

bool AsWindow::maximized()
{
	return mMaximized;
}

bool AsWindow::fullScreen()
{
	return mFullScreen;
}

AsWindowState AsWindow::state()
{
	return mState;
}

int AsWindow::exec()
{
	if (mState != WINDOW_STATE_UNSTART)
		return -1;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, mResizable);
	glfwWindowHint(GLFW_VISIBLE, mVisible);
	glfwWindowHint(GLFW_DECORATED, !mFrameless);
	glfwWindowHint(GLFW_FLOATING, mFloating);
	glfwWindowHint(GLFW_MAXIMIZED, mMaximized);

	if (mFullScreen)
		mWindow = CreateFullScreenWindow();
	else
		mWindow = CreateDefaultWindow();

	if (nullptr == mWindow)
	{
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(mWindow);
	CurrentInstanceHandleEvents();

	glfwSetKeyCallback(mWindow, DispatchKeyboardEvents);
	glfwSetMouseButtonCallback(mWindow, DispatchMouseEvents);

	int width, height;
	glfwGetFramebufferSize(mWindow, &width, &height);
	glViewport(0, 0, width, height);

	MainLoop();
	
	glfwTerminate();
	return 0;
}