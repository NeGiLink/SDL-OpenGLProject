#pragma once

#include <vector>
#include "Math.h"
#include <cstdint>
#include "CollisionActor.h"

//�S3D���f���̊��N���X
//Unity��Transform�ɋ߂����������Ă���
class ActorObject
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};
	//�R���X�g���N�^
	ActorObject(class BaseScene* game);
	//�f�X�g���N�^
	virtual ~ActorObject();
	// �Q�[������Ăяo�����X�V�֐��i�I�[�o�[���C�h�s�j
	void Update(float deltaTime);
	// Actor�ɐڑ����ꂽ���ׂẴR���|�[�l���g���X�V���܂��i�I�[�o�[���C�h�s�j
	void UpdateComponents(float deltaTime);
	// �C�ӂ�Actor�ŗL�̍X�V�R�[�h�i�㏑���\�j
	virtual void UpdateActor(float deltaTime);
	// �Q�[������Ăяo���ꂽProcessInput�֐��i�I�[�o�[���C�h�ł��܂���j
	void ProcessInput(const struct InputState& keyState);
	// �C�ӂ�Actor���L�̓��̓R�[�h�i�㏑���\�j
	virtual void ActorInput(const struct InputState& keyState);


	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	const Matrix4& GetLocalTransform() const { return mLocalTransform; }

	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitZ, mRotation); }

	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitX, mRotation); }

	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitY, mRotation); }

	void RotateToNewForward(const Vector3& forward);

	// Getters/setters
	State GetState() const { return mState; }

	void SetState(State state) { mState = state; }

	// Position��Getters/setters
	const Vector3& GetPosition() const { return mPosition; }
	void SetPosition(const Vector3& pos) 
	{
		mPosition = pos; 
		mRecomputeWorldTransform = true; 
	}
	//Position�����Z�ő����֐�
	void AddPosition(const Vector3& pos) 
	{
		mPosition += pos;
		mRecomputeWorldTransform = true;
	}
	//mPositionOffset�ɉ��Z����֐�
	void AddPositionOffset(const Vector3& pos) 
	{
		mPositionOffset += pos;
	}
	// Scale��Getters/setters
	Vector3 GetScale() const { return mScale; }
	// 1 Ver
	void SetScale(Vector3 scale) { mScale = scale;  mRecomputeWorldTransform = true; }
	// 2 Ver
	void SetScale(float scale) { mScale = Vector3(scale,scale,scale);  mRecomputeWorldTransform = true; }
	// Rotation��Getters/setters
	const Quaternion& GetRotation() const { return mRotation; }

	void SetRotation(const Quaternion& rotation) { mRotation = rotation;  mRecomputeWorldTransform = true; }
	
	void AddRotation(const Quaternion& rotation) { mRotation = rotation;  mRecomputeWorldTransform = true; }
	
	//���ʂ̉�]�ʂ�Getters/setters
	float GetRotationAmountX() { return mRotationAmountX; }
	
	float GetRotationAmountY() { return mRotationAmountY; }
	
	float GetRotationAmountZ() { return mRotationAmountZ; }

	void SetRotationAmountX(float rot) { mRotationAmountX = rot; }
	
	void SetRotationAmountY(float rot) { mRotationAmountY = rot; }
	
	void SetRotationAmountZ(float rot) { mRotationAmountZ = rot; }
	
	//���[���h���W�̍X�V
	void ComputeWorldTransform(const class Matrix4* parentMatrix);
	void ComputeLocalTransform();

	void LocalBonePositionUpdateActor(Matrix4 boneMatrix, const class Matrix4& parentActor);


	//***�q�I�u�W�F�N�g�֌W�̏���***
	// Add/remove components
	void AddComponent(class Component* component);
	
	void RemoveComponent(class Component* component);
	//�q�I�u�W�F�N�g��ǉ�
	void AddChildActor(class ActorObject* actor);
	
	void RemoveChildActor(class ActorObject* actor);
	
	const class ActorObject* GetChildActor(class ActorObject* actor);
	
	void AddParentActor(class ActorObject* parent);

	void RemoveParentActor();

	//�q�I�u�W�F�N�g�̍��W�X�V
	void SetActive() { mRecomputeWorldTransform = true; }
	


	class BaseScene* GetGame() { return mGame; }

	//�����������ɌĂяo�����֐�
	virtual void OnCollisionEnter(class ActorObject* target){}
	//�������Ă��鎞�ɌĂяo�����֐�
	virtual void OnCollisionStay(class ActorObject* target){}
	//������I��������ɌĂяo�����֐�
	virtual void OnCollisionExit(class ActorObject* target){}
private:
	// World Transform
	Matrix4		mWorldTransform;
	//Local Transform
	Matrix4		mLocalTransform;
protected:
	// Actor's state
	State							mState;

	Vector3							mPosition;

	Vector3							mPositionOffset;

	Quaternion						mRotation;

	//X�AY�AZ���̉�]��
	float							mRotationAmountX;
	float							mRotationAmountY;
	float							mRotationAmountZ;

	Vector3							mScale;

	bool							mRecomputeWorldTransform;

	std::vector<class Component*>	mComponents;
	//�e�I�u�W�F�N�g
	class ActorObject*				mParentActor;
	//�q�I�u�W�F�N�g�̔z��
	std::vector<class ActorObject*> mChildActor;

	class BaseScene*				mGame;
};