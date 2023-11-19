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
private:
	enum class BOXTYPE
	{
		CENTER = 0,
		FOOT,
		MAX,
	};

public:
	CVector3 pos;
	CVector3 size;
	BOXTYPE type = BOXTYPE::CENTER;


public:
	BoxCollider();
	BoxCollider(const CVector3& p, const CVector3& s);
	~BoxCollider();
	void SetBox(const CVector3& p, const CVector3& s);
	bool CollisionBox(const BoxCollider& Box);
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
	void setplane(CVector3 p, CVector3 n);
	void setplane(TriangleCollider t);
	void setplane(SquareCollider sq);
	float LengthPoint(CVector3 p);
	RayHitParam CollisionRay(Ray rays);
};

class TriangleCollider
{
public:
	CVector3 p[3];

public:
	TriangleCollider();
	TriangleCollider(CVector3 p1, CVector3 p2, CVector3 p3);
	TriangleCollider(CVector3* points);
	~TriangleCollider();
	void settriangle(CVector3 p1, CVector3 p2, CVector3 p3);
	void settriangle(CVector3* point);
	bool PointInner(CVector3 point);
	RayHitParam CollisionRay(Ray rays);
};

class SquareCollider
{
public:
	CVector3 p[4];

public:
	SquareCollider();
	SquareCollider(CVector3 p1, CVector3 p2, CVector3 p3, CVector3 p4);
	~SquareCollider();
	void setsquare(CVector3 p1, CVector3 p2, CVector3 p3, CVector3 p4);
	bool PointInner(CVector3 point);
	RayHitParam CollisionRay(Ray rays);

};

class Ray
{
public:
	CVector3 pos;
	CVector3 direct;
public:
	Ray();
	Ray(CVector3 p, CVector3 d);
	~Ray();
	void setray(CVector3 p, CVector3 d);
};