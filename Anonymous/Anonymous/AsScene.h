#ifndef _ANONYMOUS_SCENE_H_
#define _ANONYMOUS_SCENE_H_

#include <string>
#include "AsCamera.h"
#include "AsEmptyObject.h"
#include "AsPolygon.h"

using namespace std;
/*
\ Scene that contains game issues, including
\  camera, light, objects
*/
class AsScene
{
	/*
	\ Name of this scene
	*/
	string mName;
	/*
	\ Main camera in this scene
	*/
	AsCamera mCamera;
	/*
	\ An empty object is labeled root to manage all objects in this scene
	*/
	AsEmptyObject * mRoot;

public:
	AsScene(string name = "New Scene");
	~AsScene();
	/*
	\ Release the memory of this scene
	*/
	void Release();
	/*
	\ Update this scene
	*/
	void Update(float dt);
	/*
	\ Render this scene
	*/
	void Render(float interpolation);
};

#endif