#include "UIBase.h"
#include "Main.h"


UI_Base::UI_Base()
	:m_pTexture(nullptr)
	, m_pos({0.0f,0.0f,0.0f})
	,m_size({ 1.0f,1.0f})
	,m_UVpos({ 0.0f,0.0f})
	,m_UVsize({ 1.0f,1.0f})
{

}

UI_Base::~UI_Base()
{

}

void UI_Base::Update()
{

}

void UI_Base::Draw()
{
	DirectX::XMFLOAT4X4 fView;
	DirectX::XMStoreFloat4x4(&fView,
		DirectX::XMMatrixIdentity());

	//�A�v���W�F�N�V�����s�񂪏d�v
	//���̍s���2D�̃X�N���[���̑傫�������߂�
	DirectX::XMFLOAT4X4 fProj;
	DirectX::XMStoreFloat4x4(&fProj,
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixOrthographicOffCenterLH(
				0.0f,//��ʍ��[�̍��W
				GetAppWidth(),//��ʉE�[�̍��W
				GetAppHeight(),	//��ʉ��[�̍��W
				0.0f,	//��ʏ�[�̍��W
				-1.0f,	//2�����Ŏʂ���ŏ��l
				1.0f	//2�����Ŏʂ���ő�l
			)
		));

	//���[���h�s��ŉ�ʂ̕\���ʒu���v�Z
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(
		m_pos.x,
		m_pos.y, m_pos.z);
	DirectX::XMFLOAT4X4 fWorld;
	DirectX::XMStoreFloat4x4(&fWorld,
		DirectX::XMMatrixTranspose(T));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(fWorld);
	Sprite::SetView(fView);
	Sprite::SetProjection(fProj);
	Sprite::SetSize(m_size);
	Sprite::SetUVPos(m_UVpos);
	Sprite::SetUVScale(m_UVsize);
	Sprite::SetTexture(m_pTexture);
	Sprite::Draw();
}

void UI_Base::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}
void UI_Base::SetSize(DirectX::XMFLOAT2 size)
{
	m_size = size;
}