#pragma once
#include <vector>
#include "Math.h"
#include <cstdint>
#include "CollisionActor.h"
#include "BaseScene.h"
#include "Component.h"
#include <algorithm>

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
	ActorObject();
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

	void SetWorldTransform(Matrix4 mat) { mWorldTransform = mat; }

	const Matrix4& GetLocalTransform() const { return mModelTransform; }

	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitZ, mLocalRotation); }

	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitX, mLocalRotation); }

	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitY, mLocalRotation); }

	void RotateToNewForward(const Vector3& forward);

	// Getters/setters
	State GetState() const { return mState; }

	void SetState(State state) { mState = state; }

	// Position��Getters/setters
	const Vector3& GetLocalPosition() const { return mLocalPosition; }
	void SetPosition(const Vector3& pos) 
	{
		mLocalPosition = pos; 
		mRecomputeWorldTransform = true; 
	}
	//Position�����Z�ő����֐�
	void AddPosition(const Vector3& pos) 
	{
		mLocalPosition += pos;
		mRecomputeWorldTransform = true;
	}
	//mPositionOffset�ɉ��Z����֐�
	void AddPositionOffset(const Vector3& pos) 
	{
		mPositionOffset += pos;
	}
	// Scale��Getters/setters
	Vector3 GetLocalScale() const { return mLocalScale; }
	// 1 Ver
	void SetScale(Vector3 scale) { mLocalScale = scale;  mRecomputeWorldTransform = true; }
	// 2 Ver
	void SetScale(float scale) { mLocalScale = Vector3(scale,scale,scale);  mRecomputeWorldTransform = true; }
	// Rotation��Getters/setters
	const Quaternion& GetLocalRotation() const { return mLocalRotation; }

	void SetRotation(const Quaternion& rotation) { mLocalRotation = rotation;  mRecomputeWorldTransform = true; }
	
	void AddRotation(const Quaternion& rotation) { mLocalRotation = rotation;  mRecomputeWorldTransform = true; }
	
	//���ʂ̉�]�ʂ�Getters/setters
	float GetRotationAmountX() { return mRotationAmountX; }
	
	float GetRotationAmountY() { return mRotationAmountY; }
	
	float GetRotationAmountZ() { return mRotationAmountZ; }

	void SetRotationAmountX(float rot) { mRotationAmountX = rot; }
	
	void SetRotationAmountY(float rot) { mRotationAmountY = rot; }
	
	void SetRotationAmountZ(float rot) { mRotationAmountZ = rot; }
	
	//���[���h���W�̍X�V
	virtual void ComputeWorldTransform(const class Matrix4* parentMatrix);

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

	//TODO : �Čv�Z�p�ɐe�̃A�N�^�[���擾�ł���悤�ɒǉ�
	class ActorObject* GetParentActor() { return mParentActor; }

	//�����������ɌĂяo�����֐�
	virtual void OnCollisionEnter(class ActorObject* target){}
	//�������Ă��鎞�ɌĂяo�����֐�
	virtual void OnCollisionStay(class ActorObject* target){}
	//������I��������ɌĂяo�����֐�
	virtual void OnCollisionExit(class ActorObject* target){}

	virtual std::string GetBoneName() { return "NULL"; }
protected:
	// World Transform
	Matrix4		mWorldTransform;
	//Model Transform
	Matrix4		mModelTransform;
	// Actor's state
	State							mState;

	
	Vector3							mPosition;

	Quaternion						mRotation;

	Vector3							mScale;


	Vector3							mLocalPosition;

	Vector3							mPositionOffset;

	Quaternion						mLocalRotation;

	//X�AY�AZ���̉�]��
	float							mRotationAmountX;
	float							mRotationAmountY;
	float							mRotationAmountZ;

	Vector3							mLocalScale;

	bool							mRecomputeWorldTransform;

	std::vector<class Component*>	mComponents;
	//�e�I�u�W�F�N�g
	class ActorObject*				mParentActor;
	//�q�I�u�W�F�N�g�̔z��
	std::vector<class ActorObject*> mChildActor;

	class BaseScene*				mGame;
};