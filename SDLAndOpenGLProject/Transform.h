#pragma once
#include "Math.h"
#include "BaseScene.h"
#include "Component.h"

//�I�u�W�F�N�g�̍��W�A��]�A�X�P�[�����O�̏����Ǘ�
//Unity��Transform�ɋ߂��N���X
class Transform
{
protected:
	// World Transform
	Matrix4								mWorldTransform;
	//Model Transform
	Matrix4								mModelTransform;

	//���[���h���W�A��]�A�X�P�[�����O
	Vector3								mPosition;

	Quaternion							mRotation;

	Vector3								mScale;

	//���[�J�����W�A��]�A�X�P�[�����O
	Vector3								mLocalPosition;

	Vector3								mPositionOffset;

	Quaternion							mLocalRotation;

	//X�AY�AZ���̉�]��
	float								mRotationAmountX;
	float								mRotationAmountY;
	float								mRotationAmountZ;

	Vector3								mLocalScale;

	bool								mRecomputeWorldTransform;

	vector<class Component*>			mComponents;
	//�e�I�u�W�F�N�g
	class Transform* mParentActor;
	//�q�I�u�W�F�N�g�̔z��
	vector<class Transform*>			mChildActor;
public:
										Transform();

	virtual								~Transform();

	virtual const Matrix4&				GetWorldTransform() const { return mWorldTransform; }

	virtual void						SetWorldTransform(Matrix4 mat) { mWorldTransform = mat; }

	virtual const Matrix4&				GetLocalTransform() const { return mModelTransform; }

	virtual Vector3						GetForward() const { return Vector3::Transform(Vector3::UnitZ, mLocalRotation); }

	virtual Vector3						GetRight() const { return Vector3::Transform(Vector3::UnitX, mLocalRotation); }

	virtual Vector3						GetUp() const { return Vector3::Transform(Vector3::UnitY, mLocalRotation); }

	virtual void						RotateToNewForward(const Vector3& forward);

	virtual void						LookAt(const Vector3& targetPosition);

	// Getters/setters
	virtual const Vector3&				GetPosition() const { return mPosition; }

	virtual const Quaternion&			GetRotation() const { return mRotation; }

	virtual const Vector3&				GetScale() const { return mScale; }

	// Position��Getters/setters
	virtual const Vector3&				GetLocalPosition() const { return mLocalPosition; }

	virtual void						SetLocalPosition(const Vector3& pos)
	{
		mLocalPosition = pos;
		mRecomputeWorldTransform = true;
	}
	//Position�����Z�ő����֐�
	virtual void						AddLocalPosition(const Vector3& pos)
	{
		mLocalPosition += pos;
		mRecomputeWorldTransform = true;
	}
	//mPositionOffset�ɉ��Z����֐�
	virtual void						AddPositionOffset(const Vector3& pos)
	{
		mPositionOffset += pos;
	}
	// Scale��Getters/setters
	virtual Vector3						GetLocalScale() const { return mLocalScale; }
	// 1 Ver
	virtual void						SetLocalScale(Vector3 scale)
	{
		mLocalScale = scale;
		mRecomputeWorldTransform = true;
	}
	// 2 Ver
	virtual void						SetLocalScale(float scale)
	{
		mLocalScale = Vector3(scale, scale, scale);
		mRecomputeWorldTransform = true;
	}
	// Rotation��Getters/setters
	virtual const Quaternion&			GetLocalRotation() const { return mLocalRotation; }

	virtual void						SetLocalRotation(const Quaternion& rotation)
	{
		mLocalRotation = rotation;
		mRecomputeWorldTransform = true;
	}

	//���ʂ̉�]�ʂ�Getters/setters
	virtual float						GetRotationAmountX() { return mRotationAmountX; }

	virtual float						GetRotationAmountY() { return mRotationAmountY; }

	virtual float						GetRotationAmountZ() { return mRotationAmountZ; }

	virtual void						SetRotationAmountX(float rot) { mRotationAmountX = rot; }

	virtual void						SetRotationAmountY(float rot) { mRotationAmountY = rot; }

	virtual void						SetRotationAmountZ(float rot) { mRotationAmountZ = rot; }

	//���[���h���W�̍X�V		
	virtual void						ComputeWorldTransform(const class Matrix4* parentMatrix);

	virtual void						LocalBonePositionUpdateActor(Matrix4 boneMatrix, const class Matrix4& parentActor);

	//***�q�I�u�W�F�N�g�֌W�̏���***
	virtual class Transform*			GetParentActor() { return mParentActor; }

	virtual const class Transform*		GetChildActor(Transform* actor);

	// Add/remove components
	virtual void						AddComponent(Component* component);

	virtual void						RemoveComponent(Component* component);
	//�q�I�u�W�F�N�g��ǉ�
	virtual void						AddChildActor(Transform* actor);

	virtual void						RemoveChildActor(Transform* actor);


	virtual void						AddParentActor(Transform* parent);

	virtual void						RemoveParentActor();

	//�q�I�u�W�F�N�g�̍��W�X�V
	virtual void						SetActive() { mRecomputeWorldTransform = true; }
};

