#pragma once

#include <vector>
#include "Math.h"
#include <cstdint>
#include "CollisionActor.h"

//�S3D���f���̊��N���X
//Unity��Transform�ɋ߂����������Ă���
class ActorObject : public CollisionActor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	ActorObject(class BaseScene* game);
	virtual ~ActorObject();

	// �Q�[������Ăяo�����X�V�֐��i�I�[�o�[���C�h�s�j
	void Update(float deltaTime);
	// Actor�ɐڑ����ꂽ���ׂẴR���|�[�l���g���X�V���܂��i�I�[�o�[���C�h�s�j
	void UpdateComponents(float deltaTime);
	// �C�ӂ�Actor�ŗL�̍X�V�R�[�h�i�㏑���\�j
	virtual void UpdateActor(float deltaTime);

	// �Q�[������Ăяo���ꂽProcessInput�֐��i�I�[�o�[���C�h�ł��܂���j
	void ProcessInput(const bool* keyState);
	// �C�ӂ�Actor���L�̓��̓R�[�h�i�㏑���\�j
	virtual void ActorInput(const bool* keyState);

	void OnCollisionEnter()override;
	void OnCollisionStay()override;
	void OnCollisionExit()override;

	// Getters/setters
	const Vector3& GetPosition() const { return mPosition; }

	void SetPosition(const Vector3& pos) 
	{
		mPosition = pos; 
		mRecomputeWorldTransform = true; 
	}

	void AddPosition(const Vector3& pos) 
	{
		mPosition += pos;
		mRecomputeWorldTransform = true;
	}
	// Getters/setters
	Vector3 GetScale() const { return mScale; }
	
	void SetScale(Vector3 scale) { mScale = scale;  mRecomputeWorldTransform = true; }
	
	void SetScale(float scale) { mScale = Vector3(scale,scale,scale);  mRecomputeWorldTransform = true; }
	// Getters/setters
	const Quaternion& GetRotation() const { return mRotation; }
	
	void SetRotation(const Quaternion& rotation) { mRotation = rotation;  mRecomputeWorldTransform = true; }
	
	void AddRotation(const Quaternion& rotation) { mRotation = rotation;  mRecomputeWorldTransform = true; }

	void ComputeWorldTransform();
	
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitZ, mRotation); }
	
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitX, mRotation); }

	void RotateToNewForward(const Vector3& forward);

	// Getters/setters
	State GetState() const { return mState; }
	
	void SetState(State state) { mState = state; }

	class BaseScene* GetGame() { return mGame; }


	// Add/remove components
	void AddComponent(class Component* component);
	
	void RemoveComponent(class Component* component);
	//�q�I�u�W�F�N�g��ǉ�
	void AddChildActor(class ActorObject* actor);
	
	void RemoveChildActor(class ActorObject* actor);
	
	const class ActorObject* GetChildActor(class ActorObject* actor);
	//�q�I�u�W�F�N�g�̍��W�X�V
	void SetActive() { mRecomputeWorldTransform = true; }
	
	void SetParentActor(class ActorObject* parent) { mParentActor = parent; }
private:
	// Transform
	Matrix4		mWorldTransform;
protected:
	// Actor's state
	State							mState;

	Vector3							mPosition;

	Quaternion						mRotation;

	Vector3							mScale;

	bool							mRecomputeWorldTransform;

	std::vector<class Component*>	mComponents;
	//�e�I�u�W�F�N�g
	class ActorObject*				mParentActor;
	//�q�I�u�W�F�N�g�̔z��
	std::vector<class ActorObject*> mChildActor;

	class BaseScene*				mGame;
};