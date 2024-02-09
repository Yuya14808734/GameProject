#pragma once
#include "Calculation.h"

class LightObject
{
public:
	LightObject();
	~LightObject();

	void SetPos(const CVector3& pos);
	void SetDirection(const CVector3& Direction);
	const CVector3& GetPos() const;
	const CVector3& GetDirection() const;

private:
	CVector3 m_Pos;
	CVector3 m_Direction;
};