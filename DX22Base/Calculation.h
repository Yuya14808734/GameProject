#pragma once

#include <DirectXMath.h>

class CVector2;
class CVector3;
class CQuaternion;

class CVector2
{
public:
	union {
		struct {
			float x, y;
		};
		struct {
			float s, t;
		};
		struct {
			float u, v;
		};
		DirectX::XMFLOAT2 f;
	};

public:
	CVector2();
	CVector2(const CVector2&);
	CVector2(const CVector3&);
	CVector2(const DirectX::XMFLOAT2&);
	CVector2(float x, float y);
	CVector2(int x, int y);

	CVector2 operator + () const;
	CVector2 operator - () const;

	CVector2& operator += (const CVector2&);
	CVector2& operator -= (const CVector2&);
	CVector2& operator *= (float);
	CVector2& operator /= (float);

	CVector2 operator + (const CVector2&) const;
	CVector2 operator - (const CVector2&) const;
	CVector2 operator * (float) const;
	CVector2 operator / (float) const;

	bool operator == (const CVector2&) const;
	bool operator != (const CVector2&) const;

	float cross(CVector2&) const;
	float distance(CVector2&) const;
	float dot(CVector2&) const;
	float length() const;
	CVector2 normalize() const;
	CVector2 rotateRadius(float Radius);
	CVector2 rotateAngle(float Angle);
	CVector2 Abs() const;

	
public:
	static const CVector2& GetUp();
	static const CVector2& GetRight();
	static const CVector2& GetZero();
	static const CVector2& GetRotateRadius(float Radius);
	static const CVector2& GetAngleVector(float Angle);

private: 
	static const CVector2 m_Right;
	static const CVector2 m_Up;
	static const CVector2 m_Zero;
};

class CVector3
{
public:
	union {
		struct {
			float x, y, z;
		};
		struct {
			float r, g, b;
		};
		DirectX::XMFLOAT3 f;
	};

public:
	CVector3();
	CVector3(const CVector3&);
	CVector3(const CVector2&);
	CVector3(const CVector3*);
	CVector3(const DirectX::XMFLOAT3&);
	CVector3(float x, float y, float z);
	CVector3(int x, int y, int z);

	CVector3& operator =  (const DirectX::XMFLOAT3&);
	CVector3& operator += (const CVector3&);
	CVector3& operator -= (const CVector3&);
	CVector3& operator *= (float);
	CVector3& operator /= (float);

	//単項演算子のオーバーロード
	CVector3 operator + () const;
	CVector3 operator - () const;

	CVector3 operator + (const CVector3&) const;
	CVector3 operator - (const CVector3&) const;
	CVector3 operator * (float) const;
	CVector3 operator / (float) const;

	bool operator == (const CVector3&) const;
	bool operator != (const CVector3&) const;

	CVector3 cross(CVector3) const;
	float distance(CVector3) const;
	float dot(CVector3) const;
	float length() const;
	CVector3 normalize() const;
	CVector3 Abs() const;


public:
	static const CVector3& GetForward();
	static const CVector3& GetUp();
	static const CVector3& GetRight();
	static const CVector3& GetZero();

private:
	static const CVector3 m_Forward;
	static const CVector3 m_Right;
	static const CVector3 m_Up;
	static const CVector3 m_Zero;
};

class CQuaternion
{
public:
	DirectX::XMVECTOR v;

public:
	CQuaternion();
	CQuaternion(float x,float y,float z,float w);
	CQuaternion(float AngleX, float AngleY, float AngleZ);
	CQuaternion(CVector3 Angle);
	CQuaternion(const DirectX::XMFLOAT4& f);
	CQuaternion operator*  (const CQuaternion& q);
	CQuaternion operator*= (const CQuaternion& q);
	const CVector3& RotateVector(const CVector3& vec) const;
	const DirectX::XMFLOAT4& GetValue() const;
	const CQuaternion& normalize() const;
	void SetQuaternion(float x, float y, float z, float w);

public:
	static CQuaternion& AngleAxis(const CVector3& Axis, float Angle);
	static CQuaternion& RadianAxis(const CVector3& Axis, float Radian);
	static CQuaternion& LookAt(const CVector3& Pos);
};