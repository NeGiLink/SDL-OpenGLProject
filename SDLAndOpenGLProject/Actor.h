#pragma once
#include "BaseScene.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Transform.h"

enum ActorTag
{
	None,
	Player,
	Ground,
	Enemy,
	Recovery
};

//�S3D���f���̊��N���X
class ActorObject : public Transform
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
	virtual						~ActorObject();
	// �Q�[�������萔�ŌĂяo�����X�V�֐��i�I�[�o�[���C�h�s�j
	void						FixedUpdate(float deltaTime);
	// Actor�ɐڑ����ꂽ���ׂẴR���|�[�l���g���X�V���܂��i�I�[�o�[���C�h�s�j
	void						FixedUpdateComponents(float deltaTime);
	// �C�ӂ�Actor�ŗL�̍X�V�R�[�h�i�㏑���\�j
	virtual void				FixedUpdateActor(float deltaTime);
	// �Q�[������Ăяo�����X�V�֐��i�I�[�o�[���C�h�s�j
	void						Update(float deltaTime);
	// Actor�ɐڑ����ꂽ���ׂẴR���|�[�l���g���X�V���܂��i�I�[�o�[���C�h�s�j
	void						UpdateComponents(float deltaTime);
	// �C�ӂ�Actor�ŗL�̍X�V�R�[�h�i�㏑���\�j
	virtual void				UpdateActor(float deltaTime);
	// �Q�[������Ăяo���ꂽProcessInput�֐��i�I�[�o�[���C�h�ł��܂���j
	void						ProcessInput(const struct InputState& keyState);
	// �C�ӂ�Actor���L�̓��̓R�[�h�i�㏑���\�j
	virtual void				ActorInput(const struct InputState& keyState);

	// Getters/setters
	State						GetState() const { return mState; }

	void						SetState(State state) { mState = state; }

	virtual ActorTag			GetActorTag() { return mActorTag; }

	void						SetActorTag(ActorTag tag) { mActorTag = tag; }
	
	class BaseScene*			GetGame() { return mGame; }
	class Rigidbody*			GetRigidbody() { return mRigidbody; }

	class Collider*				GetCollider() { return mCollider; }


	//�e�̃A�N�^�[��Getter
	//�����������ɌĂяo�����֐�
	virtual void				OnCollisionEnter(ActorObject* target){}
	//�������Ă��鎞�ɌĂяo�����֐�
	virtual void				OnCollisionStay(ActorObject* target){}
	//������I��������ɌĂяo�����֐�
	virtual void				OnCollisionExit(ActorObject* target){}
protected:
	// Actor's state
	State						mState;

	//�I�u�W�F�N�g�̃^�O
	ActorTag					mActorTag = ActorTag::None;

	BaseScene*					mGame;

	Rigidbody*					mRigidbody;

	Collider*					mCollider;
};