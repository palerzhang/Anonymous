#include "AsWindow.h"
#include "Foundation\AsPreprocessor.h"
#include "AsPolygon.h"

/*
\ Version 1.0.0
\ draw a rotatable triangle
*/

AsWindow * AsWindow::sInstanceHandleEvents = nullptr;

void AsWindow::DispatchKeyboardEvents(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	AS_UNUSED(window);
	AS_UNUSED(scancode);
	if (AsWindow::sInstanceHandleEvents)
		AsWindow::sInstanceHandleEvents->KeyboardEvent(AsKeyCode(key), AsKeyAction(action), AsModifierCode(mode));
}

void AsWindow::DispatchMouseEvents(GLFWwindow* window, int button, int action, int mode)
{
	AS_UNUSED(window);
	if (AsWindow::sInstanceHandleEvents)
		AsWindow::sInstanceHandleEvents->MouseEvent(AsMouseCode(button), AsMouseAction(action), AsModifierCode(mode));
}

void AsWindow::DispatchResizeEvents(GLFWwindow* window, int width, int height)
{
	AS_UNUSED(window);
	if (AsWindow::sInstanceHandleEvents)
		AsWindow::sInstanceHandleEvents->ResizeEvent(width, height);
}

void AsWindow::Render(float interpolation)
{
	glClearColor(mBackground.r, mBackground.g, mBackground.b, mBackground.a);
	glClear(GL_COLOR_BUFFER_BIT);

	mScene->Render(interpolation);

	glfwSwapBuffers(mWindow);
}

void AsWindow::InitWindowEnvironment()
{
	if (mState != WINDOW_STATE_UNSTART)
		return;

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
		return;
	}

	glfwMakeContextCurrent(mWindow);
	CurrentInstanceHandleEvents();
	glfwSetKeyCallback(mWindow, DispatchKeyboardEvents);
	glfwSetMouseButtonCallback(mWindow, DispatchMouseEvents);
	glfwSetFramebufferSizeCallback(mWindow, DispatchResizeEvents);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
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

void AsWindow::KeyboardEvent(AsKeyCode key, AsKeyAction action, AsModifierCode mod)
{
	if (key == AsKeyCode::KEY_ESCAPE && action == AsKeyAction::KEY_PRESS)
		glfwSetWindowShouldClose(mWindow, GL_TRUE);
}

void AsWindow::MouseEvent(AsMouseCode button, AsMouseAction action, AsModifierCode mod)
{
	// TODO
}

void AsWindow::ResizeEvent(int width, int height)
{
	glViewport(0, 0, width, height);
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

		if (nullptr != mScene)
			delete mScene;
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
		Render(interpolation);
	}
}

void AsWindow::PrepareAndCompileShaders()
{
	mScene->PrepareAndCompileShaders();
}

AsWindow::AsWindow(int posx, int posy, int w, int h, const string & title)
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

	mScene = nullptr;
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

void AsWindow::SetWindowFlag(AsWindowFlag flag, bool enable)
{
	switch (flag)
	{
	case AsWindowFlag::WINDOW_FLAG_RESIZABLE:
	{
		mResizable = enable;
	}
		break;
	case AsWindowFlag::WINDOW_FLAG_VISIBLE:
	{
		mVisible = enable;
	}
		break;
	case AsWindowFlag::WINDOW_FLAG_FRAMELESS:
	{
		mFrameless = enable;
	}
		break;
	case AsWindowFlag::WINDOW_FLAG_FLOATING:
	{
		mFloating = enable;
	}
		break;
	case AsWindowFlag::WINDOW_FLAG_FULLSCREEN:
	{
		mMaximized = enable;
	}
		break;
	case AsWindowFlag::WINDOW_FLAG_MAXIMIZED:
	{
		mFullScreen = enable;

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
		break;
	}
}

bool AsWindow::GetWindowFlag(AsWindowFlag flag)
{
	switch (flag)
	{
	case AsWindowFlag::WINDOW_FLAG_RESIZABLE:
	{
		return mResizable;
	}
		break;
	case AsWindowFlag::WINDOW_FLAG_VISIBLE:
	{
		return mVisible;
	}
		break;
	case AsWindowFlag::WINDOW_FLAG_FRAMELESS:
	{
		return mFrameless;
	}
		break;
	case AsWindowFlag::WINDOW_FLAG_FLOATING:
	{
		return mFloating;
	}
		break;
	case AsWindowFlag::WINDOW_FLAG_FULLSCREEN:
	{
		return mMaximized;
	}
		break;
	case AsWindowFlag::WINDOW_FLAG_MAXIMIZED:
	{
		return mFullScreen;
	}
		break;
	default:
	{
		return false;
	}
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

AsWindowState AsWindow::state()
{
	return mState;
}

int AsWindow::exec()
{
	InitWindowEnvironment();

	ConstructScene();

	PrepareAndCompileShaders();

	MainLoop();
	
	glfwTerminate();
	return 0;
}