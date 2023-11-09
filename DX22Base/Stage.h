//#pragma once
#ifndef STAGE_H_
#define STAGE_H_

#include <DirectXMath.h>
#include "Geometory.h"
#include "CameraBase.h"

enum POS_TYPE
{
	MIDDLE = 0,		//����
	EDGE			//�[
};

class Stage {
public: 
	struct Info {
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 size;
		DirectX::XMFLOAT3 rot;
	};
	
	struct Vertices {
		DirectX::XMFLOAT3 pos[8];
		DirectX::XMMATRIX mat;
	};


public :
	Stage() : m_pBlocks(nullptr), m_blockNum(20) {
		/*�K�v�ȃu���b�N�̐����l���A�u���b�N�̏���ݒ肷��*/
		m_pBlocks = new Info[m_blockNum];

		POS_TYPE Type = EDGE;

		CreateDrawBox(0.0f, 0.0f, 0.0f, 9.0f, 1.0f, 8.0f,Type);
		CreateDrawBox(7.0f, 1.0f, 2.0f, 2.0f, 1.0f, 4.0f,Type);
		CreateDrawBox(0.0f, 1.0f, 4.0f, 7.0f, 2.0f, 4.0f,Type);
		CreateDrawBox(7.0f, 1.0f, 6.0f, 2.0f, 2.0f, 2.0f,Type);
		CreateDrawBox(0.0f, 0.0f, 8.0f, 6.0f, 5.0f, 3.0f, Type);
		CreateDrawBox(7.0f, 3.0f, 9.0f, 1.0f, 1.0f, 1.0f, Type);
		float Hankei = sqrtf(2.0f * 2.0f + 2.0f * 2.0f);

		CreateDrawBox(1.0f, 3.0f, 8.0f, 2.0f, Hankei, Hankei, -45.0f, 0.0f, 0.0f, MIDDLE);
	}

	~Stage() {
		delete[] m_pBlocks;
	}

	void Draw() {
		for (int i = 0; i < CreateBoxNum; ++i)
		{
			SetGeometoryTranslate(m_pBlocks[i].pos.x, m_pBlocks[i].pos.y, m_pBlocks[i].pos.z);
			SetGeometoryScaling(m_pBlocks[i].size.x, m_pBlocks[i].size.y, m_pBlocks[i].size.z);
			SetGeometoryRotation(m_pBlocks[i].rot.x, m_pBlocks[i].rot.y, m_pBlocks[i].rot.z);
			DrawBox();
		}
	}

	Info* GetInfo()
	{
		return m_pBlocks;
	}

	Info getBlockInfo(unsigned int index) { return m_pBlocks[index]; }
	int GetBlockNum() { return m_blockNum; }
	Vertices GetBlockVertices(unsigned int index)
	{
		Vertices vtx = {};
		//�u���b�N�̒��_�����S�̒n�_����ǂ̕����ɂ��邩
		DirectX::XMFLOAT3 stride[] = {
			DirectX::XMFLOAT3(-1,1,1),DirectX::XMFLOAT3(1,1,1),DirectX::XMFLOAT3(-1,1,-1),
			DirectX::XMFLOAT3(1,1,-1),DirectX::XMFLOAT3(-1,-1,1),DirectX::XMFLOAT3(1,-1,1),
			DirectX::XMFLOAT3(-1,-1,-1),DirectX::XMFLOAT3(1,-1,-1), 
		};

		DirectX::XMVECTOR vCenter = DirectX::XMLoadFloat3(&m_pBlocks[index].pos);/*�u���b�N�̒��S���W*/
		DirectX::XMFLOAT3 half = DirectX::XMFLOAT3(
			m_pBlocks[index].size.x * 0.5f, m_pBlocks[index].size.y * 0.5f, m_pBlocks[index].size.z * 0.5f
		);

		DirectX::XMMATRIX mRot = /*�u���b�N�̉�]�s��*/
			DirectX::XMMatrixRotationX(m_pBlocks[index].rot.x) * 
			DirectX::XMMatrixRotationY(m_pBlocks[index].rot.y) *
			DirectX::XMMatrixRotationZ(m_pBlocks[index].rot.z);

		vtx.mat = mRot;

		for (int i = 0; i < 8; ++i)
		{
			//�e���̒��S����̋������v�Z
			DirectX::XMVECTOR pos = DirectX::XMVectorSet(
				half.x * stride[i].x, half.y * stride[i].y, half.z * stride[i].z, 0.0f);

			//�u���b�N�̔�������]�ɍ��킹�Ĉړ�������
			pos = DirectX::XMVector3TransformCoord(pos, mRot);

			//�u���b�N����]�����Ă���A���S���W�܂ňړ�������
			DirectX::XMStoreFloat3(&vtx.pos[i], DirectX::XMVectorAdd(pos, vCenter));
		}
		return vtx;
	}


private:
	Info* m_pBlocks;
	int m_blockNum;

	int CreateBoxNum = 0;

private:
	void CreateDrawBox(float PosX, float PosY, float PosZ, float SizeX, float SizeY, float SizeZ, float Angle_AxisX, float Angle_AxisY, float Angle_AxisZ, POS_TYPE type);
	void CreateDrawBox(float PosX, float PosY, float PosZ, float SizeX, float SizeY, float SizeZ, POS_TYPE type);
};

#endif	//
