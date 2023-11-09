#include "GAMEUI.h"
#include "Sprite.h"
#include "DirectXTex/Texture.h"

GameUI::GameUI()
{
	LoadTextureFromFile("Assets/2D/Glass19.png",
		&m_pNazoBar);
}


GameUI::~GameUI()
{
	m_pNazoBar->Release();
}

void GameUI::Draw()
{
	//2D�\���̂��߂̍s���ݒ�
	//�@�r���[�s��̓J�����̈ʒu���֌W�Ȃ��̂�
	//����������Ă�s����g��
	/*�P�ʍs��
	|�P�O�O�O|
	|�O�P�O�O|
	|�O�O�P�O|
	|�O�O�O�P|
	*/

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
			1280.0f,//��ʉE�[�̍��W
			720.0f,	//��ʉ��[�̍��W
			0.0f,	//��ʏ�[�̍��W
			-1.0f,	//2�����Ŏʂ���ŏ��l
			1.0f	//2�����Ŏʂ���ő�l
			)
		));

	//���[���h�s��ŉ�ʂ̕\���ʒu���v�Z
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(
		1100.0f,
		680.0f, 0.0f);
	DirectX::XMFLOAT4X4 fWorld;
	DirectX::XMStoreFloat4x4(&fWorld,
		DirectX::XMMatrixTranspose(T));

	//�X�v���C�g�̐ݒ�
	Sprite::SetWorld(fWorld);
	Sprite::SetView(fView);
	Sprite::SetProjection(fProj);
	Sprite::SetSize(DirectX::XMFLOAT2(300.0f, -20.0f));
	Sprite::SetUVPos(DirectX::XMFLOAT2(0.0f, 0.0f));
	Sprite::SetUVScale(DirectX::XMFLOAT2(1.0f, 1.0f));
	Sprite::SetTexture(m_pNazoBar);
	Sprite::Draw();

}