#pragma once
#include "BaseCamera.h"
#include "Actor.h"

//�w�肵���������f���J����
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

