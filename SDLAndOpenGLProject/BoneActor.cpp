#include "BoneActor.h"

void BoneActor::ComputeWorldTransform(const Matrix4* parentMatrix)
{
	//更新フラグがtrueなら
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;

		mModelTransform = Matrix4::CreateScale(mLocalScale);
		mModelTransform *= Matrix4::CreateFromQuaternion(mLocalRotation);
		mModelTransform *= Matrix4::CreateTranslation(mLocalPosition + mBoneMatrix.GetTranslation());


		//親がいたら
		if (parentMatrix) {
			mWorldTransform = mModelTransform * (*parentMatrix);
		}
		//いなかったら
		else {
			mWorldTransform = mModelTransform;
		}
		//子オブジェクトの座標計算
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
