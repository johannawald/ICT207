#include "GameObject.h"

GameObject::GameObject(Vector3D& pPosition, Vector3D& pMovement, Vector3D& pSize, Vector3D& pScale, Vector3D& pRotation, 
					   eModels pModelIndex, eTextures pTextureIndex, int pCollisionIndex):
	mPosition(pPosition), mMovement(pMovement), mScale(pScale), mSize(pSize), mRotation(pRotation), mModelIndex(pModelIndex), mTextureIndex(pTextureIndex), mCollisionIndex(pCollisionIndex)
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
/*
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
}*/

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

void GameObject::Draw(ModelManager* pModelManager)
{
	glTranslatef(mPosition.x, mPosition.y, mPosition.z);
	glScalef(mScale.x, mScale.y, mScale.z);
	if (mRotation.x>0)
		glRotatef(mRotation.x, 1, 0, 0);
	if (mRotation.y>0)
		glRotatef(mRotation.y, 0, 1, 0);
	if (mRotation.z>0)
		glRotatef(mRotation.z, 0, 0, 1);
	if (mModelIndex>=0)
		pModelManager->drawModel(mModelIndex, mTextureIndex);
}