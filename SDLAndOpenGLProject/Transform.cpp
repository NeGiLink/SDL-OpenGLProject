#include "Transform.h"

Transform::Transform()
	: mPosition(Vector3::Zero)
	, mLocalPosition(Vector3::Zero)
	, mPositionOffset(Vector3::Zero)
	, mRotation(Quaternion::Identity)
	, mLocalRotation(Quaternion::Identity)
	, mRotationAmountX(0)
	, mRotationAmountY(0)
	, mRotationAmountZ(0)
	, mScale(Vector3(1.0f, 1.0f, 1.0f))
	, mLocalScale(Vector3(1.0f, 1.0f, 1.0f))
	, mRecomputeWorldTransform(true)
	, mWorldTransform()
	, mModelTransform()
{
}

Transform::~Transform()
{
}

void Transform::RotateToNewForward(const Vector3& forward)
{
	// Figure out difference between original (unit x) and new
	float dot = Vector3::Dot(Vector3::UnitZ, forward);
	float angle = Math::Acos(dot);
	// Facing down X
	if (dot > 0.9999f)
	{
		SetLocalRotation(Quaternion::Identity);
	}
	// Facing down -X
	else if (dot < -0.9999f)
	{
		SetLocalRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	}
	else
	{
		// Rotate about axis from cross product
		Vector3 axis = Vector3::Cross(Vector3::UnitZ, forward);
		axis.Normalize();
		SetLocalRotation(Quaternion(axis, angle));
	}
}

void Transform::LookAt(const Vector3& targetPosition)
{
	Vector3 currentPosition = mPosition; // もしくは mLocalPosition など用途に応じて
	Vector3 forward = targetPosition - currentPosition;
	forward.Normalize();

	// Z軸をforward方向に合わせる
	float dot = Vector3::Dot(Vector3::UnitZ, forward);
	float angle = Math::Acos(dot);

	if (dot > 0.9999f)
	{
		SetLocalRotation(Quaternion::Identity);
	}
	else if (dot < -0.9999f)
	{
		SetLocalRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	}
	else
	{
		Vector3 axis = Vector3::Cross(Vector3::UnitZ, forward);
		axis.Normalize();
		SetLocalRotation(Quaternion(axis, angle));
	}

	mRecomputeWorldTransform = true;
}

void Transform::ComputeWorldTransform(const Matrix4* parentMatrix)
{
	//更新フラグがtrueなら
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;

		mModelTransform = Matrix4::CreateScale(mLocalScale);
		mModelTransform *= Matrix4::CreateFromQuaternion(mLocalRotation);
		mModelTransform *= Matrix4::CreateTranslation(mLocalPosition);


		//親がいたら
		if (parentMatrix) {
			mWorldTransform = mModelTransform * (*parentMatrix);
		}
		//いなかったら
		else {
			mWorldTransform = mModelTransform;
		}
		mPosition = mWorldTransform.GetTranslation();
		mRotation = mWorldTransform.GetRotation();
		mScale = mWorldTransform.GetScale();

		// Inform components world transform updated
		for (auto comp : mComponents)
		{
			comp->OnUpdateWorldTransform();
		}
	}
	//一時的な修正
	//子オブジェクトの座標計算
	for (auto child : mChildActor)
	{
		child->SetActive();
		child->ComputeWorldTransform(&mWorldTransform);
	}
}

void Transform::LocalBonePositionUpdateActor(Matrix4 boneMatrix, const Matrix4& parentActor)
{
	Vector3 position = parentActor.GetTranslation() + boneMatrix.GetTranslation();
	position += mPositionOffset;
	SetLocalPosition(position);
	Quaternion r = Quaternion(boneMatrix.GetRotation());
	r = Quaternion::Concatenate(r, Quaternion(Vector3::UnitX, mRotationAmountX));
	r = Quaternion::Concatenate(r, Quaternion(Vector3::UnitY, mRotationAmountY));
	r = Quaternion::Concatenate(r, Quaternion(Vector3::UnitZ, mRotationAmountZ));
	SetLocalRotation(r);
}

const Transform* Transform::GetChildActor(Transform* actor)
{
	for (Transform* a : mChildActor) {
		if (a == actor) {
			return a;
		}
	}
	return nullptr;
}

void Transform::AddComponent(Component* component)
{
	// Find the insertion point in the sorted vector
// (The first element with a order higher than me)
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;
		iter != mComponents.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mComponents.insert(iter, component);
}

void Transform::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}

void Transform::AddChildActor(Transform* actor)
{
	for (Transform* a : mChildActor)
	{
		if (a == actor) { return; }
	}
	// 親になるアクターの行列を再計算
	ComputeWorldTransform(mParentActor != nullptr ? &mParentActor->GetWorldTransform() : nullptr);
	Matrix4 parentInvert = mWorldTransform;
	parentInvert.Invert();

	// 子になるアクターの行列を再計算
	auto parentActor = actor->GetParentActor();
	actor->ComputeWorldTransform(parentActor != nullptr ? &parentActor->GetWorldTransform() : nullptr);
	Matrix4 child = actor->GetWorldTransform();

	//親になるアクターの逆行列を掛けて子のアクターの親基準のローカル情報を計算して設定
	Matrix4 childLocal = child * parentInvert;
	actor->SetLocalPosition(childLocal.GetTranslation());
	actor->SetLocalRotation(childLocal.GetRotation());
	actor->SetLocalScale(childLocal.GetScale());


	actor->AddParentActor(this);
	mChildActor.push_back(actor);

	//親子関係構築後の再計算
	mRecomputeWorldTransform = true;
}

void Transform::RemoveChildActor(Transform* child)
{
	auto iter = std::find(mChildActor.begin(), mChildActor.end(), child);
	if (iter != mChildActor.end())
	{
		child->AddParentActor(nullptr);
		mChildActor.erase(iter);
	}
}

void Transform::AddParentActor(Transform* parent)
{
	mParentActor = parent;
}

void Transform::RemoveParentActor()
{
	mParentActor = nullptr;
}
