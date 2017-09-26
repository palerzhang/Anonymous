#ifndef _ANONYMOUS_TEXTURE_2D_
#define _ANONYMOUS_TEXTURE_2D_

#include <glad\glad.h>
#include <Foundation\AsTypes.h>
#include <Foundation\AsColor.h>
#include <string>

using namespace std;

// Wrap mode
#define AS_REPEAT			GL_REPEAT
#define AS_MIRRORED_REPEAT	GL_MIRRORED_REPEAT
#define AS_CLAMP_TO_EDGE	GL_CLAMP_TO_EDGE
#define AS_CLAMP_TO_BORDER	GL_CLAMP_TO_BORDER

// Filtering
#define AS_NEAREST	GL_NEAREST
#define AS_LINEAR	GL_LINEAR
// Mipmap filtering
#define AS_NEAREST_MIPMAP_NEAREST	GL_NEAREST_MIPMAP_NEAREST
#define AS_LINEAR_MIPMAP_NEAREST	GL_LINEAR_MIPMAP_NEAREST
#define AS_NEAREST_MIPMAP_LINEAR	GL_NEAREST_MIPMAP_LINEAR
#define AS_LINEAR_MIPMAP_LINEAR		GL_LINEAR_MIPMAP_LINEAR

// Texture mode
#define AS_RGB	GL_RGB
#define AS_RGBA GL_RGBA

// Texture unit
#define AS_TEXTURE0		GL_TEXTURE0
#define AS_TEXTURE1		GL_TEXTURE1
#define AS_TEXTURE2		GL_TEXTURE2
#define AS_TEXTURE3		GL_TEXTURE3
#define AS_TEXTURE4		GL_TEXTURE4
#define AS_TEXTURE5		GL_TEXTURE5
#define AS_TEXTURE6		GL_TEXTURE6
#define AS_TEXTURE7		GL_TEXTURE7
#define AS_TEXTURE8		GL_TEXTURE8
#define AS_TEXTURE9		GL_TEXTURE9
#define AS_TEXTURE10	GL_TEXTURE10
#define AS_TEXTURE11	GL_TEXTURE11
#define AS_TEXTURE12	GL_TEXTURE12
#define AS_TEXTURE13	GL_TEXTURE13
#define AS_TEXTURE14	GL_TEXTURE14
#define AS_TEXTURE15	GL_TEXTURE15

class AsTexture2D
{
public:
	/*
	\ Texture ID
	*/
	AsUint mID;
	/*
	\ Wrap mode of texture
	\ Refer to @AS_REPEAT @AS_MIRRORED_REPEAT @AS_CLAMP_TO_EDGE @AS_CLAMP_TO_BORDER
	\ set and get
	*/
	AsUint mWrapMode;
	/*
	\ Border color when using @AS_CLAMP_TO_BORDER
	\ Other wrap mode will ignore this
	\ set and get
	*/
	AsColor mBorder;
	/*
	\ Filtering
	\ Magnify and Minify
	\ Note that minify can use mipmap filtering but magnify can not
	*/
	AsUint mMagnifyFilter;
	AsUint mMinifyFilter;
	/*
	\ Texture image file path
	*/
	string mFile;
	/*
	\ Texture unit
	*/
	AsUint mUnit;
	/*
	\ Texture mode, rgb or rgba
 	*/
	AsUint mTextureMode;
	/*
	\ Constructor and deconstructor
	*/
	AsTexture2D();
	~AsTexture2D();
	/*
	\ Generate 2d texture with configs above
	*/
	void GenerateTexture2D();
	/*
	\ Active texture before use it
	*/
	void ActiveTexture();
};

#endif