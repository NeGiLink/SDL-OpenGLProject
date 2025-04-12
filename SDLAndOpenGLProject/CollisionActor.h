#pragma once



class CollisionActor
{
public:
	virtual void OnCollisionEnter() = 0;
	virtual void OnCollisionStay()= 0;
	virtual void OnCollisionExit()= 0;
};

