#pragma once
#include "BaseCamera.h"
#include "Actor.h"

/*
* ===�G���W����������/Engine internal processing===
*/

//�w�肵���������f���J����
//FreeCamera�́A���[�U�[�����R�ɃJ�����̈ʒu�ƌ����𐧌�ł���J�����ł��B
//Component���p�����Ă���̂ŁAActorObject�ɃA�^�b�`���Ďg�p���܂��B
class FreeCamera : public BaseCamera
{
private:
	bool	isUpdatePosition;

	// �J�����̏�����x�N�g���B
	Vector3		mUp;
public:
			FreeCamera(class ActorObject* owner);

	void    Initiailze();

	void	Update(float deltaTime) override;

	void    SetCameraPosition(const Vector3& eye, const Vector3& target);
};

