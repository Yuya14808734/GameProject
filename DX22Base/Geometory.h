#ifndef __GEOMETORY_H__
#define __GEOMETORY_H__

#include "DirectX.h"
#include <DirectXMath.h>
#include "Calculation.h"

HRESULT InitGeometory();
void UninitGeometory();
void SetGeometoryTranslate(const CVector3& v);
void SetGeometoryTranslate(float x, float y, float z);
void SetGeometoryRotation(const CVector3& v);
void SetGeometoryRotation(float x, float y, float z);
void SetGeometoryScaling(const CVector3& v);
void SetGeometoryScaling(float x, float y, float z);
void SetGeometoryVPMatrix(DirectX::XMFLOAT4X4 view, DirectX::XMFLOAT4X4 proj);
void DrawPlane();
void DrawBox();
void DrawSphere();
void DrawCylinder();
void DrawCone();
void DrawCapsule();
void DrawArrow();

#endif // __GEOMETORY_H__