#include "BoneActor.h"

void BoneActor::ComputeWorldTransform(const Matrix4* parentMatrix)
{
	//�X�V�t���O��true�Ȃ�
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;

		mModelTransform = Matrix4::CreateScale(mLocalScale);
		mModelTransform *= Matrix4::CreateFromQuaternion(mLocalRotation);
		mModelTransform *= Matrix4::CreateTranslation(mLocalPosition + mBoneMatrix.GetTranslation());


		//�e��������
		if (parentMatrix) {
			mWorldTransform = mModelTransform * (*parentMatrix);
		}
		//���Ȃ�������
		else {
			mWorldTransform = mModelTransform;
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
