#pragma once



class CollisionActor
{
public:
	//�����������ɌĂяo�����֐�
	virtual void OnCollisionEnter(class ActorObject* target) = 0;
	//�������Ă��鎞�ɌĂяo�����֐�
	virtual void OnCollisionStay(class ActorObject* target)= 0;
	//������I��������ɌĂяo�����֐�
	virtual void OnCollisionExit(class ActorObject* target)= 0;
};

