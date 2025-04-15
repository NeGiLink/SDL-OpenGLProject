#pragma once
#include <cstdint>

//�R���|�[�l���g�̊��N���X
class Component
{
public:
	// �R���X�g���N�^
	// �i�X�V�������Ⴂ�قǁA�R���|�[�l���g�������X�V�����j
	Component(class ActorObject* owner, int updateOrder = 100);
	// �f�X�g���N�^�[
	virtual ~Component();
	// �f���^���Ԃł��̃R���|�[�l���g���X�V���Ă�������
	virtual void Update(float deltaTime);
	// ���̃R���|�[�l���g�̓��͂���������
	virtual void ProcessInput(const struct InputState& keyState) {}
	// ���E�̕ω��ɂ���ČĂяo�����
	virtual void OnUpdateWorldTransform() { }

	class ActorObject* GetOwner() { return mOwner; }
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	// �R���|�[�l���g���̃I�u�W�F�N�g
	class ActorObject* mOwner;
	// �R���|�[�l���g�̏������X�V����
	int mUpdateOrder;
};