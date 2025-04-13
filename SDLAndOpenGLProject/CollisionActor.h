#pragma once



class CollisionActor
{
public:
	//当たった時に呼び出される関数
	virtual void OnCollisionEnter(class ActorObject* target) = 0;
	//当たっている時に呼び出される関数
	virtual void OnCollisionStay(class ActorObject* target)= 0;
	//当たり終わった時に呼び出される関数
	virtual void OnCollisionExit(class ActorObject* target)= 0;
};

