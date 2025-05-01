#include "Actor.h"

ActorObject::ActorObject()
	:mState(EActive)
	, mLocalPosition(Vector3::Zero)
	, mPositionOffset(Vector3::Zero)
	, mLocalRotation(Quaternion::Identity)
	, mRotationAmountX(0)
	, mRotationAmountY(0)
	, mRotationAmountZ(0)
	, mLocalScale(Vector3(1.0f,1.0f,1.0f))
	, mGame(GameApp::GetActiveScene())
	, mRecomputeWorldTransform(true)
{
	mGame->AddActor(this);
}

ActorObject::~ActorObject()
{
	mGame->RemoveActor(this);
	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void ActorObject::Update(float deltaTime)
{
	if (mState == EActive)
	{
		//ComputeLocalTransform();
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
		ComputeWorldTransform(NULL);
	}
}

void ActorObject::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void ActorObject::UpdateActor(float deltaTime)
{
}

void ActorObject::ProcessInput(const struct InputState& keyState)
{
	if (mState == EActive)
	{
		// First process input for components
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keyState);
		}

		ActorInput(keyState);
	}
}

void ActorObject::ActorInput(const struct InputState& keyState)
{
}

void ActorObject::ComputeWorldTransform(const class Matrix4 *parentMatrix)
{
	//�X�V�t���O��true�Ȃ�
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;

		mModelTransform = Matrix4::CreateScale(mLocalScale);
		mModelTransform *= Matrix4::CreateFromQuaternion(mLocalRotation);
		mModelTransform *= Matrix4::CreateTranslation(mLocalPosition);


		//�e��������
		if (parentMatrix) {
			mWorldTransform = mModelTransform * (*parentMatrix);
		}
		//���Ȃ�������
		else {
			mWorldTransform = mModelTransform;
		}
		mPosition = mWorldTransform.GetTranslation();
		mRotation = mWorldTransform.GetRotation();
		mScale =	mWorldTransform.GetScale();
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

void ActorObject::LocalBonePositionUpdateActor(Matrix4 boneMatrix, const Matrix4& parentActor)
{
	Vector3 position = parentActor.GetTranslation() + boneMatrix.GetTranslation();
	position += mPositionOffset;
	SetPosition(position);
	Quaternion r = Quaternion(boneMatrix.GetRotation());
	r = Quaternion::Concatenate(r, Quaternion(Vector3::UnitX, mRotationAmountX));
	r = Quaternion::Concatenate(r, Quaternion(Vector3::UnitY, mRotationAmountY));
	r = Quaternion::Concatenate(r, Quaternion(Vector3::UnitZ, mRotationAmountZ));
	SetRotation(r);
}

void ActorObject::RotateToNewForward(const Vector3& forward)
{
	// Figure out difference between original (unit x) and new
	float dot = Vector3::Dot(Vector3::UnitX, forward);
	float angle = Math::Acos(dot);
	// Facing down X
	if (dot > 0.9999f)
	{
		SetRotation(Quaternion::Identity);
	}
	// Facing down -X
	else if (dot < -0.9999f)
	{
		SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	}
	else
	{
		// Rotate about axis from cross product
		Vector3 axis = Vector3::Cross(Vector3::UnitX, forward);
		axis.Normalize();
		SetRotation(Quaternion(axis, angle));
	}
}

void ActorObject::AddComponent(Component* component)
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

void ActorObject::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}

void ActorObject::AddChildActor(ActorObject* actor)
{
	for (ActorObject* a : mChildActor) 
	{
		if (a == actor) { return; }
	}
	// �e�ɂȂ�A�N�^�[�̍s����Čv�Z�A
	// ���g�̐e���炵���v�Z���Ă��Ȃ��̂Őe�̍X�V���l�����Ă��Ȃ����ߕs�\��
	ComputeWorldTransform(mParentActor != nullptr ? &mParentActor->GetWorldTransform() : nullptr);
	Matrix4 parentInvert = mWorldTransform;
	parentInvert.Invert();

	// �q�ɂȂ�A�N�^�[�̍s����Čv�Z�A
	// ���g�̐e���炵���v�Z���Ă��Ȃ��̂Őe�̍X�V���l�����Ă��Ȃ����ߕs�\��
	auto parentActor = actor->GetParentActor();
	actor->ComputeWorldTransform(parentActor != nullptr ? &parentActor->GetWorldTransform() : nullptr);
	Matrix4 child = actor->GetWorldTransform();

	//�e�ɂȂ�A�N�^�[�̋t�s����|���Ďq�̃A�N�^�[�̐e��̃��[�J�������v�Z���Đݒ�
	Matrix4 childLocal = child * parentInvert;
	actor->SetPosition(childLocal.GetTranslation());
	actor->SetRotation(childLocal.GetRotation());
	actor->SetScale(childLocal.GetScale());


	actor->AddParentActor(this);
	mChildActor.push_back(actor);

	//TODO: �e�q�֌W�\�z��̍Čv�Z
	mRecomputeWorldTransform = true;
}

void ActorObject::RemoveChildActor(ActorObject* actor)
{
	auto iter = std::find(mChildActor.begin(), mChildActor.end(), actor);
	if (iter != mChildActor.end())
	{
		actor->AddParentActor(nullptr);
		mChildActor.erase(iter);
	}
}

const ActorObject* ActorObject::GetChildActor(ActorObject* actor)
{
	for (ActorObject* a : mChildActor) {
		if (a == actor) {
			return a;
		}
	}
	return nullptr;
}

void ActorObject::AddParentActor(ActorObject* parent)
{
	mParentActor = parent;
}

void ActorObject::RemoveParentActor()
{
	mParentActor = nullptr;
}
