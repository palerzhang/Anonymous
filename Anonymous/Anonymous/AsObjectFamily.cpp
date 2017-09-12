#include "AsObjectFamily.h"
#include "AsObject.h"


AsObjectFamily::AsObjectFamily(AsObject * parent)
{
	mParent = parent;
	mChildren.clear();
}

AsObjectFamily::~AsObjectFamily()
{
	Release();
}

AsObjectMap & AsObjectFamily::GetChildren()
{
	return mChildren;
}

AsObject * AsObjectFamily::FindChild(const string & name)
{
	AsObjectMapIter iter = mChildren.find(name);
	if (iter == mChildren.end())
		return nullptr;
	return iter->second;
}

AsObject * AsObjectFamily::GetParent()
{
	return mParent;
}

void AsObjectFamily::Attach(AsObject * parent)
{
	mParent = parent;
}

void AsObjectFamily::Release()
{
	mParent = nullptr;
	// Release every child
	AsObjectMapIter iter;
	for (iter = mChildren.begin(); iter != mChildren.end(); ++iter)
		delete iter->second;
}