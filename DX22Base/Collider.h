#pragma once
//�����蔻�����������N���X
//�l�p
//��
//����
//���C

#include "Calculation.h"

class BoxCollider;
class SphereCollider;
class PlaneCollider;
class TriangleCollider;
class SquareCollider;
class Ray;

class BoxCollider
{
public:
	//�^�C�v������ɂ͂��邯��
	//�����蔻��̏���������Ƃ���
	//���g�͑S���^�񒆂ɕϊ�������
	enum class BOXTYPE
	{
		CENTER = 0,
		FOOT,
		MAX,
	};

private:
	CVector3 m_BasePos;
	CVector3 m_ShiftPosVector;
	CVector3 m_size;
	BOXTYPE m_type = BOXTYPE::CENTER;


public:
	BoxCollider();
	BoxCollider(const CVector3& p, const CVector3& s);
	BoxCollider(const CVector3& p, const CVector3& s,const CVector3& shiftP);
	~BoxCollider();
	void CreateBox(BoxCollider::BOXTYPE type, const CVector3& pos, const CVector3& size,const CVector3& shiftPos = CVector3::GetZero());
	void SetBasePos(const CVector3& pos);
	const CVector3& GetBasePos() const;
	void SetShiftVec(const CVector3& shiftVec);
	const CVector3& GetShiftVec() const;
	void SetColliderPos(const CVector3& pos);
	CVector3 GetColliderPos() const;
	void SetSize(const CVector3& size);
	const CVector3& GetSize() const;
	void SetType(BoxCollider::BOXTYPE type);
	BoxCollider::BOXTYPE GetType() const;
	bool CollisionBox(const BoxCollider& Box);
	void DrawCollider();
};

class SphereCollider
{
public:
	CVector3 pos;
	float radius;

public:
	SphereCollider();
	SphereCollider(CVector3 p, float r);
	~SphereCollider();
	void SetSphere(CVector3 p, float r);
	bool CollisionSphere(SphereCollider Sphere);
	bool CollisionSphere(CVector3 point);
};

class RayHitParam
{
public:
	bool Hit;
	CVector3 HitPos;
};

class PlaneCollider
{
private:
	float a;
	float b;
	float c;
	float d;
public:
	PlaneCollider();
	PlaneCollider(CVector3 p, CVector3 n);
	PlaneCollider(TriangleCollider t);
	PlaneCollider(SquareCollider sq);
	~PlaneCollider();
	void setplane(const CVector3& p,const CVector3& n);
	void setplane(const TriangleCollider& t);
	void setplane(const SquareCollider& sq);
	float LengthPoint(const CVector3& p);
	RayHitParam CollisionRay(const Ray& rays);
};

class TriangleCollider
{
public:
	CVector3 p[3];

public:
	TriangleCollider();
	TriangleCollider(const CVector3& p1, const CVector3& p2, const CVector3& p3);
	TriangleCollider(CVector3* points);
	~TriangleCollider();
	void settriangle(const CVector3& p1, const CVector3& p2, const CVector3& p3);
	void settriangle(CVector3* point);
	bool PointInner(const CVector3& point);
	RayHitParam CollisionRay(const Ray& rays);
};

class SquareCollider
{
public:
	CVector3 p[4];

public:
	SquareCollider();
	SquareCollider(const CVector3& p1, const CVector3& p2, const CVector3& p3, const CVector3& p4);
	~SquareCollider();
	void setsquare(const CVector3& p1, const CVector3& p2, const CVector3& p3, const CVector3& p4);
	bool PointInner(const CVector3& point);
	RayHitParam CollisionRay(const Ray& rays);

};

class Ray
{
public:
	CVector3 pos;
	CVector3 direct;
public:
	Ray();
	Ray(const CVector3& p, const CVector3& d);
	~Ray();
	void setray(const CVector3& p, const CVector3& d);
};