#include "Light.h"

LightObject::LightObject()
	:m_Pos(CVector3(0.0f,0.0f,-10.0f)),
	m_Direction(CVector3(0.0f,0.0f,1.0f))
{
}

LightObject::~LightObject()
{
}

void LightObject::SetPos(const CVector3& pos)
{
	m_Pos = pos;
}

void LightObject::SetDirection(const CVector3& Direction)
{
	m_Direction = Direction;
}

const CVector3& LightObject::GetPos() const
{
	return m_Pos;
}

const CVector3& LightObject::GetDirection() const
{
	return m_Direction;
}
