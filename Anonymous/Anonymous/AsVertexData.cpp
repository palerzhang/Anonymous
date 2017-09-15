#include "AsVertexData.h"
#include <stdlib.h>
#include <string.h>

AsVertexData::AsVertexData(AsVertexFlag flag)
{
	mData = nullptr;
	mFlag = flag | AS_POSITION;
	mCount = 0;
}

AsVertexData::~AsVertexData()
{
	Release();
}

void AsVertexData::Allocate(int num)
{
	mCount = num;
	int size = 0;
	if (AS_POSITION & mFlag)
		size += 3;
	if (AS_NORMAL & mFlag)
		size += 3;
	if (size != 0)
		mData = (float *)malloc(size * sizeof(float) * num);
}

void AsVertexData::LoadData(float * position, float * normal)
{
	if (nullptr == position)
		return;
	AsUint size = 3 * sizeof(float);
	if ((AS_NORMAL & mFlag))
	{
		AsUint offset1;
		AsUint offset2;
		for (AsUint i = 0; i < mCount; i++)
		{
			offset1 = 6 * i;
			offset2 = 3 * i;
			memmove(mData + offset1, position + offset2, size);
			memmove(mData + offset1 + 3, normal + offset2, size);
		}
	}
	else
	{
		memmove(mData, position, size * mCount);
	}
}

void AsVertexData::Release()
{
	if (nullptr != mData)
		free(mData);
}
