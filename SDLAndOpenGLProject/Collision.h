#pragma once
#include "Math.h"
#include <vector>

//�e�����蔻��̍\���̂��܂Ƃ߂��t�@�C��
//�{�b�N�X�A���A���Ȃ�

struct LineSegment
{
	LineSegment(const Vector3& start, const Vector3& end);
	// 0 <= t <= 1 �̊Ԃ̃Z�O�����g�ɉ������_���擾����
	Vector3 PointOnSegment(float t) const;
	// �_�Ɛ����̍ŏ������̓����擾����
	float MinDistSq(const Vector3& point) const;
	// 2�̐����Ԃ̍ŏ�������2����擾����
	static float MinDistSq(const LineSegment& s1, const LineSegment& s2);

	Vector3 mStart;
	Vector3 mEnd;
};

struct Plane
{
	Plane(const Vector3& normal, float d);
	// 3�̓_���畽�ʂ��\�z����
	Plane(const Vector3& a, const Vector3& b, const Vector3& c);
	// �_�ƕ��ʂ̊Ԃ̕����t���������擾����
	float SignedDist(const Vector3& point) const;

	Vector3 mNormal;
	float mD;
};

struct Sphere
{
	Sphere(const Vector3& center, float radius);
	bool Contains(const Vector3& point) const;

	Vector3 mCenter;
	float mRadius;
};

struct AABB
{
	AABB(const Vector3& min, const Vector3& max);
	// ���̃|�C���g���l�����čŏ��l�ƍő�l���X�V����
	// (���f����ǂݍ��ނƂ��Ɏg�p����܂�)
	void UpdateMinMax(const Vector3& point);
	// �N�H�[�^�j�I���ɂ���ĉ�]����܂���
	void Rotate(const Quaternion& q);
	bool Contains(const Vector3& point) const;
	float MinDistSq(const Vector3& point) const;

	Vector3 mMin;
	Vector3 mMax;
};

struct OBB
{
	Vector3 mCenter;
	Quaternion mRotation;
	Vector3 mExtents;
};

struct Capsule
{
	Capsule(const Vector3& start, const Vector3& end, float radius);
	// 0 <= t <= 1 �̊Ԃ̃Z�O�����g�ɉ������_���擾����
	Vector3 PointOnSegment(float t) const;
	bool Contains(const Vector3& point) const;

	LineSegment mSegment;
	float mRadius;
};

struct ConvexPolygon
{
	bool Contains(const Vector2& point) const;
	// ���_�͎��v���ɕ��ׂ��Ă��܂�
	std::vector<Vector2> mVertices;
};

// �����_�@�\
bool Intersect(const Sphere& a, const Sphere& b);
bool Intersect(const AABB& a, const AABB& b);
bool Intersect(const Capsule& a, const Capsule& b);
bool Intersect(const Sphere& s, const AABB& box);

bool Intersect(const LineSegment& l, const Sphere& s, float& outT);
bool Intersect(const LineSegment& l, const Plane& p, float& outT);
bool Intersect(const LineSegment& l, const AABB& b, float& outT,
	Vector3& outNorm);

bool SweptSphere(const Sphere& P0, const Sphere& P1,
	const Sphere& Q0, const Sphere& Q1, float& t);
