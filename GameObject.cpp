#include "GameObject.h"

GameObject::GameObject(Vector3D& pPosition, Vector3D& pMovement, Vector3D& pScale, eModels pModelIndex, eTextures pTextureIndex, int pCollisionIndex):
	mPosition(pPosition), mMovement(pMovement), mScale(pScale), mModelIndex(pModelIndex), mTextureIndex(pTextureIndex), mCollisionIndex(pCollisionIndex)
{
	mPositionOriginal = mPosition;
}

float GameObject::GetXPosition()
{
	return mPosition.x;
}

float GameObject::GetYPosition()
{
	return mPosition.y;
}

float GameObject::GetZPosition()
{
	return mScale.z;
}

float GameObject::GetXScale()
{
	return mScale.x;
}

float GameObject::GetYScale()
{
	return mScale.y;
}

float GameObject::GetZScale()
{
	return mScale.z;
}

eModels GameObject::getModelIndex()
{
	return mModelIndex;
}

eTextures GameObject::getTextureIndex()
{
	return mTextureIndex;
}

void GameObject::Transform(float x, float y, float z)
{
	mPosition.x = mPositionOriginal.x + x;
	mPosition.y = mPositionOriginal.y + y;
	mPosition.z = mPositionOriginal.z + z;
}
