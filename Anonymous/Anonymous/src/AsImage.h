#ifndef _ANONYMOUS_IMAGE_
#define _ANONYMOUS_IMAGE_

#include "AsObject.h"
#include "AsVertexData.h"
#include "AsShader.h"
#include "AsTexture2D.h"
#include <Foundation\AsColor.h>
#include <Foundation\AsTypes.h>

/*
\ The image class.
\ Polygon is usually used in 2D (3D is ok)
*/
class AsImage : public AsObject
{
	/*
	\ Vertex of the image
	\ This is private because this will never change
	\ The region of the image is always
	\ -0.5, -0.5 -> 0.5, 0.5
	\ Change the scale once the scale is implemented
	*/
	AsVertexData * mVertex;
public:
	/*
	\ Color
	*/
	AsColor mColor;
	/*
	\ Texture
	*/
	AsTexture2D * mTexture;
	/*
	\ Shader of image
	*/
	AsShader * mShader;
	/*
	\ Width and height of the image
	*/
	AsFloat mWidth;
	AsFloat mHeight;
	/*
	\ Constructor
	*/
	AsImage(string name = "New Image", AsObject * parent = nullptr);
	/*
	\ Deconstructor
	*/
	~AsImage();
	/*
	\ Free the memory
	*/
	void Release() override;
	/*
	\ Render the shape
	*/
	void Render(float interpolation) override;
	/*
	\ Prepare and compile shader
	\ i.e. set some uniforms if needed
	*/
	void PrepareAndCompileShaders() override;
};

#endif