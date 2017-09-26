#include "AsVertexData.h"
#include <stdlib.h>
#include <string.h>
#include <glad\glad.h>

AsVertexData::AsVertexData()
{
	mCount = 0;
	mVAO = 0;
	mVBO = 0;
	mEBO = 0;
	mLoaded = false;
}

AsVertexData::~AsVertexData()
{
	Release();
}

void AsVertexData::LoadData(const float * data, AsLoadFlag flag, AsUint vsize, const AsUint * indices, AsUint isize, AsUint usage)
{
	if (mLoaded || nullptr == data)
		return;

	AsUint vbufsize = (flag == FLAG_NORMAL_ONLY || flag == FLAG_POSITION_ONLY ? vsize * 3 : vsize * 6);

	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mEBO);

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, vbufsize  * sizeof(float), data, usage);

	switch (flag)
	{
	case FLAG_POSITION_ONLY:
	{
		glVertexAttribPointer(ATTRIBUTE_POSITION_POSITION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(ATTRIBUTE_POSITION_POSITION);
	}
		break;
	case FLAG_NORMAL_ONLY:
	{
		glVertexAttribPointer(ATTRIBUTE_POSITION_NORMAL, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(ATTRIBUTE_POSITION_NORMAL);
	}
		break;
	case FLAG_POSITION_NORMAL:
	{
		glVertexAttribPointer(ATTRIBUTE_POSITION_POSITION, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(ATTRIBUTE_POSITION_POSITION);

		glVertexAttribPointer(ATTRIBUTE_POSITION_NORMAL, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(ATTRIBUTE_POSITION_NORMAL);
	}
		break;
	case FLAG_NORMAL_POSITION:
	{
		glVertexAttribPointer(ATTRIBUTE_POSITION_NORMAL, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(ATTRIBUTE_POSITION_NORMAL);

		glVertexAttribPointer(ATTRIBUTE_POSITION_POSITION, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(ATTRIBUTE_POSITION_POSITION);
	}
		break;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	if (nullptr == indices)
	{
		isize = vsize;
		AsUint * deflt = (AsUint *)malloc(vsize * sizeof(AsUint));
		for (AsUint i = 0; i < vsize; i++)
			deflt[i] = i;
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, vsize * sizeof(AsUint), deflt, usage);
		free(deflt);
	}
	else
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, isize * sizeof(AsUint), indices, usage);

	mCount = isize;
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void AsVertexData::Release()
{
	if (mLoaded)
	{
		glDeleteVertexArrays(1, &mVAO);
		glDeleteBuffers(1, &mVBO);
		glDeleteBuffers(1, &mEBO);
	}
}

void AsVertexData::RenderSelf(AsUint mode)
{
	glBindVertexArray(mVAO);
	glDrawElements(mode, mCount, GL_UNSIGNED_INT, 0);
}
