#pragma once
//当たり判定を実装するクラス
//四角
//球
//平面
//レイ

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
	//タイプがあるにはあるけど
	//中身は全部真ん中で処理をする
	enum class BOXTYPE
	{
		CENTER = 0,
		FOOT,
		MAX,
	};

private:
	CVector3 m_pos;
	CVector3 m_size;
	BOXTYPE m_type = BOXTYPE::CENTER;


public:
	BoxCollider();
	BoxCollider(const CVector3& p, const CVector3& s);
	~BoxCollider();
	void SetPos(const CVector3& pos);
	const CVector3& GetPos() const;
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