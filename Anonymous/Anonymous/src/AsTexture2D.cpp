#include "AsTexture2D.h"
#include <STB\stb_image.h>
#include <iostream>

AsTexture2D::AsTexture2D()
{
	mUnit = AS_TEXTURE0;
	mFile = "";
	mID = 0;
}

AsTexture2D::~AsTexture2D()
{

}

void AsTexture2D::GenerateTexture2D()
{
	// Try to read file first
	int w, h, c;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(mFile.c_str(), &w, &h, &c, 0);
	if (!data)
	{
		// Load fail
		cout << "FAILED TO LOAD TEXTURE IMAGE FILE.\n";
		stbi_image_free(data);
		return;
	}
	AsUint file_mode = (c == 4 ? AS_RGBA : AS_RGB);

	glGenTextures(1, &mID);
	glBindTexture(GL_TEXTURE_2D, mID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrapMode);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mMinifyFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mMagnifyFilter);

	glTexImage2D(GL_TEXTURE_2D, 0, mTextureMode, w, h, 0, file_mode, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

void AsTexture2D::ActiveTexture()
{
	glActiveTexture(mUnit);
	glBindTexture(GL_TEXTURE_2D, mID);
}