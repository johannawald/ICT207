#include "GameObject.h"

GameObject::GameObject(Vector3D& pPosition, Vector3D& pMovement, 
					   Vector3D& pSize, Vector3D& pScale, Vector3D& pRotation, 
					   int pModelIndex, GLuint pTextureIndex, int pTexCoordX, int pTexCoordY, int pCollisionIndex):
					 //  , void (GameController::*pCollisionMethod)(void)):
		mPosition(pPosition), mMovement(pMovement), 
		mScale(pScale), mSize(pSize), mRotation(pRotation), 
		mTexCoordX(pTexCoordX), mTexCoordY(pTexCoordY), mTextureIndex(pTextureIndex), mCollisionIndex(pCollisionIndex)
		//, mCollisionMethod(pCollisionMethod)
{
	mPositionOriginal = mPosition;
	mModelIndex = (eModels)pModelIndex;
}

void GameObject::Transform(const Vector3D& pTransform)
{
	mPosition = mPositionOriginal + pTransform;
}

void GameObject::Move(const Vector3D& pTransform)
{
	mPositionOriginal = mPositionOriginal + pTransform;
	mPosition = mPositionOriginal + pTransform;
}

void GameObject::Draw(ModelManager& pModelManager, DrawManager& pDrawManger, CollisionDetection& pCollision)
{
	if (mModelIndex>-1)
	{
		glTranslatef(mPosition.x, mPosition.y, mPosition.z);
		glScalef(mScale.x, mScale.y, mScale.z);
		if (mRotation.x>0)
			glRotatef(mRotation.x, 1, 0, 0);
		if (mRotation.y>0)
			glRotatef(mRotation.y, 0, 1, 0);
		if (mRotation.z>0)
			glRotatef(mRotation.z, 0, 0, 1);
		pModelManager.drawModel(mModelIndex, mTextureIndex);
	}
	else 
		pDrawManger.DrawCollisionRect(&pCollision, mTextureIndex, mTexCoordX, mTexCoordY, mPosition, mSize.x, mSize.y, mSize.z);
}
