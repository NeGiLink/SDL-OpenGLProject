#include "BoneActor.h"

void BoneActor::ComputeWorldTransform(const Matrix4* parentMatrix)
{
	//�X�V�t���O��true�Ȃ�
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;

		mModelTransform = Matrix4::CreateScale(mLocalScale);
		mModelTransform *= Matrix4::CreateFromQuaternion(mLocalRotation);
		mModelTransform *= Matrix4::CreateTranslation(mLocalPosition);

		//�e��������
		if (parentMatrix) 
		{
			mWorldTransform = mModelTransform * (*parentMatrix);
		}
		//���Ȃ�������
		else 
		{
			//�{�[���̃}�g���b�N�X�Ƀ��f�����g�̃}�g���b�N�X����Z
			mWorldTransform = mModelTransform * parentActor->GetLocalTransform();
		}
		//�q�I�u�W�F�N�g�̍��W�v�Z
		for (auto child : mChildActor)
		{
			child->SetActive();
			child->ComputeWorldTransform(&mWorldTransform);
		}

		// Inform components world transform updated
		for (auto comp : mComponents)
		{
			comp->OnUpdateWorldTransform();
		}
	}
}
