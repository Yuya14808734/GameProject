#include "Collider.h"
#include "Geometory.h"

//=====================================================================
//四角当たり判定

BoxCollider::BoxCollider()
	:BoxCollider(CVector3(0.0f,0.0f,0.0f),CVector3(1.0f,1.0f,1.0f))
{
	
}

BoxCollider::BoxCollider(const CVector3& p, const CVector3& s)
	:m_pos(p),
	m_size(s),
	m_type(BoxCollider::BOXTYPE::CENTER)
{

}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::CreateBox(BoxCollider::BOXTYPE type, const CVector3 & pos, const CVector3 & size)
{
	SetType(type);
	SetPos(pos);
	SetSize(size);
}

void BoxCollider::SetPos(const CVector3& pos)
{
	switch (m_type)
	{
	case BoxCollider::BOXTYPE::CENTER:
		m_pos = pos;
		break;
	case BoxCollider::BOXTYPE::FOOT:
		m_pos = pos;
		m_pos.y += m_size.y * 0.5f;
		break;
	case BoxCollider::BOXTYPE::MAX:
		break;
	default:
		break;
	}
}

const CVector3& BoxCollider::GetPos() const
{
	return m_pos;
}

void BoxCollider::SetSize(const CVector3& size)
{
	switch (m_type)
	{
	case BoxCollider::BOXTYPE::CENTER:
		m_size = size;
		break;
	case BoxCollider::BOXTYPE::FOOT:
		m_pos.y -= m_size.y * 0.5f;	//一度足元に位置を戻す
		m_size = size;				//サイズを設定
		m_pos.y += m_size.y * 0.5f;	//真ん中にする
		break;
	case BoxCollider::BOXTYPE::MAX:
		break;
	default:
		break;
	}
}

const CVector3& BoxCollider::GetSize() const
{
	return m_size;
}

void BoxCollider::SetType(BoxCollider::BOXTYPE type)
{
	m_type = type;
}

BoxCollider::BOXTYPE BoxCollider::GetType() const
{
	return m_type;
}


bool BoxCollider::CollisionBox(const BoxCollider& Box)
{
	bool temp = false;

	CVector3 NowDistance;
	CVector3 ColliderHarfSize;

	NowDistance = Box.GetPos() - this->GetPos();
	NowDistance = NowDistance.Abs();
	ColliderHarfSize = (this->GetSize() + Box.GetSize()) * 0.5f;

	if (ColliderHarfSize.x > NowDistance.x &&
		ColliderHarfSize.y > NowDistance.y &&
		ColliderHarfSize.z > NowDistance.z)
	{
		temp = true;
	}

	return temp;
}

void BoxCollider::DrawCollider()
{
	SetGeometoryTranslate(m_pos.x, m_pos.y, m_pos.z);
	SetGeometoryRotation(0.0f, 0.0f, 0.0f);
	SetGeometoryScaling(m_size.x, m_size.y, m_size.z);
	DrawBox();
}

//=====================================================================
//球当たり判定

SphereCollider::SphereCollider()
{
	SetSphere(CVector3::GetZero(), 1.0f);
}

SphereCollider::SphereCollider(CVector3 p, float r)
{
	SetSphere(p, r);
}
SphereCollider::~SphereCollider()
{

}

void SphereCollider::SetSphere(CVector3 p, float r)
{
	pos = p;
	radius = r;
}

bool SphereCollider::CollisionSphere(SphereCollider Sphere)
{
	bool temp = {};

	float NowDistance =
		((pos.x - Sphere.pos.x) * (pos.x - Sphere.pos.x)) +
		((pos.y - Sphere.pos.y) * (pos.y - Sphere.pos.y)) +
		((pos.z - Sphere.pos.z) * (pos.z - Sphere.pos.z));

	float HitDistance = (radius + Sphere.radius) * (radius + Sphere.radius);

	if (NowDistance < HitDistance)
		temp = true;

	return temp;
}

bool SphereCollider::CollisionSphere(CVector3 point)
{
	//自分の位置とポイントの距離を求める
	CVector3 v = point - pos;
	if (v.x * v.x + v.y * v.y + v.z * v.z < radius * radius)
	{
		return true;
	}

	return false;
}

//=====================================================================
//面当たり判定

PlaneCollider::PlaneCollider()
{
	//平面のa,b,cを設定
	a = 0.0f;
	b = 1.0f;
	c = 0.0f;

	//平面のdを設定
	d = -((0.0f * 0.0f) + (1.0f * 0.0f) + (0.0f * 0.0f));
}

PlaneCollider::PlaneCollider(CVector3 p, CVector3 n)
{
	setplane(p, n);
}

PlaneCollider::PlaneCollider(TriangleCollider t)
{
	setplane(t);
}

PlaneCollider::PlaneCollider(SquareCollider sq)
{
	setplane(sq);
}

PlaneCollider::~PlaneCollider()
{

}

void PlaneCollider::setplane(CVector3 p, CVector3 n)
{
	//法線を正規化しておく
	n = n.normalize();

	//平面のa,b,cを設定
	a = n.x;
	b = n.y;
	c = n.z;

	//平面のdを設定
	d = -((n.x * p.x) + (n.y * p.y) + (n.z * p.z));
}

void PlaneCollider::setplane(TriangleCollider t)
{
	CVector3 v0, v1;
	v0 = t.p[1] - t.p[0];
	v1 = t.p[2] - t.p[1];
	CVector3 dotvec = v0.cross(v1);

	setplane(t.p[0], dotvec);
}

void PlaneCollider::setplane(SquareCollider sq)
{
	CVector3 v0, v1;
	v0 = sq.p[1] - sq.p[0];
	v1 = sq.p[2] - sq.p[1];
	CVector3 dotvec = v0.cross(v1);

	setplane(sq.p[0], dotvec);
}

float PlaneCollider::LengthPoint(CVector3 p)
{
	float l;
	l = a * p.x + b * p.y + c * p.z + d;
	return l;
}

RayHitParam PlaneCollider::CollisionRay(Ray rays)
{
	RayHitParam temp = {};

	float spd = LengthPoint(rays.pos);
	float epd = LengthPoint(rays.pos + rays.direct);

	//Rayの始点が0だった場合
	if (spd == 0.0f)
	{
		temp.Hit = true;
		temp.HitPos = rays.pos;
		return temp;
	}

	if (epd == 0.0f)
	{
		temp.Hit = true;
		temp.HitPos = rays.pos + rays.direct;
		return temp;
	}

	//Rayが平面を突き抜けていない場合
	if (!((spd > 0.0f) && (epd < 0.0f) || (spd < 0.0f) && (epd > 0.0f)))
	{
		temp.Hit = false;
		return temp;
	}

	//ここまで来たら当たっている
	temp.Hit = true;

	//内積を使ってレイが面に当たるまでの距離を求める
	CVector3 rayVecN = rays.direct.normalize();		//正規化
	float HitDist = 0.0f;							//Rayの長さを入れる
	if (spd > 0.0f)
	{
		//Rayが表から来ている場合
		float VecCos = rayVecN.dot(CVector3(-a, -b, -c));
		HitDist = spd / VecCos;
	}
	else
	{
		//Rayが裏から来ている場合
		float VecCos = rayVecN.dot(CVector3(a, b, c));
		HitDist = spd / VecCos;
	}

	//
	temp.HitPos = rays.pos + (rayVecN * HitDist);

	return temp;
}

//=====================================================================
//三角形当たり判定
TriangleCollider::TriangleCollider()
{
	settriangle(CVector3(0.0f, 0.0f, 0.0f), CVector3(1.0f, 0.0f, 0.0f), CVector3(0.0f, 0.0f, 1.0f));
}

TriangleCollider::TriangleCollider(CVector3 p1, CVector3 p2, CVector3 p3)
{
	settriangle(p1, p2, p3);
}

TriangleCollider::TriangleCollider(CVector3* points)
{
	settriangle(points);
}

TriangleCollider::~TriangleCollider()
{

}

void TriangleCollider::settriangle(CVector3 p1, CVector3 p2, CVector3 p3)
{
	p[0] = p1;
	p[1] = p2;
	p[2] = p3;
}

void TriangleCollider::settriangle(CVector3* point)
{
	settriangle(point[0], point[1], point[2]);
}

bool TriangleCollider::PointInner(CVector3 checkpoint)
{
	bool temp = false;

	//各頂点からポイントに向かうベクトル
	CVector3 vt0 = checkpoint - p[0];
	CVector3 vt1 = checkpoint - p[1];
	CVector3 vt2 = checkpoint - p[2];

	//各頂点から次の座標に向かうベクトル
	CVector3 v0 = p[1] - p[0];
	CVector3 v1 = p[2] - p[1];
	CVector3 v2 = p[0] - p[2];

	//外積を使ってポイントの向きを調べる
	CVector3 c0 = v0.cross(vt0);
	CVector3 c1 = v1.cross(vt1);
	CVector3 c2 = v2.cross(vt2);

	//内積を使って外積のベクトルの向きを調べる
	float d0 = c0.dot(c1);
	float d1 = c1.dot(c2);

	if (d0 > 0.0f && d1 > 0.0f)
	{
		temp = true;
	}

	return temp;
}

RayHitParam TriangleCollider::CollisionRay(Ray rays)
{
	RayHitParam tempparam = {};
	PlaneCollider copyplane(*this);	//このポリゴンを面にする

	//Rayと面が当たっているかの情報
	RayHitParam rayhitparam = copyplane.CollisionRay(rays);

	//面に当たっていなかった場合
	if (!rayhitparam.Hit)
	{
		tempparam.Hit = false;
		return tempparam;
	}

	//面に当たっている位置が三角形の中か確認
	if (!this->PointInner(rayhitparam.HitPos))
	{
		tempparam.Hit = false;
		return tempparam;
	}

	//上の二つ(面に当たっている、当たっている場所が三角形の中)をクリアしている
	return rayhitparam;
}

//=====================================================================
//四角形当たり判定

SquareCollider::SquareCollider()
{
	setsquare(CVector3(-0.5f, 0.0f, 0.5f), CVector3(0.5f, 0.0f, 0.5f), CVector3(-0.5f, 0.0f, -0.5f), CVector3(0.5f, 0.0f, -0.5f));
}

SquareCollider::SquareCollider(CVector3 p1, CVector3 p2, CVector3 p3, CVector3 p4)
{
	setsquare(p1, p2, p3, p4);
}

SquareCollider::~SquareCollider()
{

}

void SquareCollider::setsquare(CVector3 p1, CVector3 p2, CVector3 p3, CVector3 p4)
{
	p[0] = p1;
	p[1] = p2;
	p[2] = p3;
	p[3] = p4;
}

bool SquareCollider::PointInner(CVector3 checkpoint)
{
	bool temp = false;

	//三角形を使って調べる
	TriangleCollider t1(p[0], p[1], p[2]);
	TriangleCollider t2(p[1], p[2], p[3]);

	if (t1.PointInner(checkpoint))
	{
		temp = true;
	}
	else if (t2.PointInner(checkpoint))
	{
		temp = true;
	}

	return temp;
}

RayHitParam SquareCollider::CollisionRay(Ray rays)
{
	RayHitParam tempparam = {};
	PlaneCollider copyplane(*this);	//このポリゴンを面にする

	//Rayと面が当たっているかの情報
	RayHitParam rayhitparam = copyplane.CollisionRay(rays);

	//面に当たっていなかった場合
	if (!rayhitparam.Hit)
	{
		tempparam.Hit = false;
		return tempparam;
	}

	//面に当たっている位置が四角形の中か確認
	if (!this->PointInner(rayhitparam.HitPos))
	{
		tempparam.Hit = false;
		return tempparam;
	}

	//上の二つ(面に当たっている、当たっている場所が三角形の中)をクリアしている
	return rayhitparam;
}

//=====================================================================
//レイ当たり判定

Ray::Ray(CVector3 p, CVector3 d)
{
	setray(p, d);
}

Ray::~Ray()
{

}

void Ray::setray(CVector3 p, CVector3 d)
{
	pos = p;
	direct = d;
}