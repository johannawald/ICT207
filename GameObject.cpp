#include "GameObject.h"

GameObject::GameObject(Vector3D& pPosition, Vector3D& pMovement, Vector3D& pSize, Vector3D& pScale, eModels pModelIndex, eTextures pTextureIndex, int pCollisionIndex):
	mPosition(pPosition), mMovement(pMovement), mScale(pScale), mSize(pSize), mModelIndex(pModelIndex), mTextureIndex(pTextureIndex), mCollisionIndex(pCollisionIndex)
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
	return mPosition.z;
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

Vector3D& GameObject::GetSize()
{
	return mSize;
}

eModels GameObject::getModelIndex()
{
	return mModelIndex;
}

eTextures GameObject::getTextureIndex()
{
	return mTextureIndex;
}

void GameObject::Transform(Vector3D pTransform)
{
	mPosition = mPositionOriginal + pTransform;
}

void GameObject::Move(Vector3D pTransform)
{
	mPositionOriginal = mPositionOriginal + pTransform;
	mPosition = mPositionOriginal + pTransform;
}
