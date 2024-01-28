#include "VersusCharacterPanelMove.h"
#include "ShaderManager.h"

// ================================================================
// 
// �L�����N�^�[���p�l���̌`�ɂ���ʂ����摜��`�悷��N���X
//s
// ================================================================

ShapeCutCharacterPanel::ShapeCutCharacterPanel()
	:m_pCharacterImage(nullptr)
{
	//�萔�o�b�t�@�[�̍쐬
	m_ConstantBuffer_SecondTextureUV = new ConstantBuffer();
	m_ConstantBuffer_SecondTextureUV->Create(sizeof(DirectX::XMFLOAT4));

	//�V�F�[�_�[�̐ݒ�
	SetVertexShader(ShaderManager::CreateVertexShader(
		"MultiplyTextureVS", CreateShaderPath("MultiplyTextureVS")
	));
	SetPixelShader(ShaderManager::CreatePixelShader(
		"MultiplyTexturePS_ShapeCut", CreateShaderPath("MultiplyTexturePS_ShapeCut")
	));

	//�J�b�g������`���������摜
	SetTexture("Assets/UI/CharacterBackPanel_White.png");
	m_size = CVector2(147.0f, 320.0f) * 1.8f;	//�T�C�Y�̐ݒ�
}

ShapeCutCharacterPanel::~ShapeCutCharacterPanel()
{
	if (m_pCharacterImage != nullptr)
	{
		m_pCharacterImage->Release();
		m_pCharacterImage = nullptr;
	}

	delete m_ConstantBuffer_SecondTextureUV;
	m_ConstantBuffer_SecondTextureUV = nullptr;
}

void ShapeCutCharacterPanel::PrevDraw()
{
	//�V�F�[�_�[�ɃL�����N�^�[�̉摜����n��
	SetTexturePS(m_pCharacterImage, 1);

	DirectX::XMFLOAT4 UVParam;

	UVParam.x = m_UVPos_Character.x;
	UVParam.y = m_UVPos_Character.y;
	UVParam.z = m_UVSize_Character.x;
	UVParam.w = m_UVSize_Character.y;

	m_ConstantBuffer_SecondTextureUV->Write(&UVParam);
	m_ConstantBuffer_SecondTextureUV->BindVS(2);
}

void ShapeCutCharacterPanel::SetCharacterImage(SelectCharacterList::CHARACTER Character)
{
	if (m_pCharacterImage != nullptr)
	{
		m_pCharacterImage->Release();
		m_pCharacterImage = nullptr;
	}

	//�L�����N�^�[�̉摜�̐ݒ�
	switch (Character)
	{
	case SelectCharacterList::CHARACTER::UNITYCHAN:
	case SelectCharacterList::CHARACTER::MAX:
	case SelectCharacterList::CHARACTER::NONE:
		LoadTextureFromFile("Assets/CharacterImage/StandImage_UnityChan.png", &m_pCharacterImage);
		m_BaseImageSize_Character = CVector2(435.0f,640.0f);
		SetCharacterUVPos(CVector2(0.1f, -0.05f));
		SetCharacterUVScale(0.5f);
		break;
	}
}

void ShapeCutCharacterPanel::SetCharacterUVPos(const CVector2& pos)
{
	m_UVPos_Character = pos;
}

void ShapeCutCharacterPanel::SetCharacterUVScale(float Scale)
{
	//====<�L�����N�^�[��UV�T�C�Y�����߂�>=====
	//�L�����N�^�[�摜�ƃp�l���̉摜�ő傫�����Ⴄ�̂�
	//�L�����N�^�[�摜�̑傫�����w�肵�Ă����
	//�p�l���̉摜�ł���ʂ��悤�ȏ��������Ă��Ȃ��Ƃ����Ȃ�

	//�p�l���ɉf���T�C�Y��ݒ�
	CVector2 CharacterImageSize = m_BaseImageSize_Character * Scale;

	//��ŋ��߂��T�C�Y���p�l���̃T�C�Y�̂ǂꂭ�炢�̊����������߂�
	m_UVSize_Character.x = 147.0f / CharacterImageSize.x;
	m_UVSize_Character.y = 320.0f / CharacterImageSize.y;
}

// ================================================================
// 
// ��̃N���X(�L�����N�^�[�̕`��)�ƌ��̃p�l�������킹���N���X
// �܂��p�l���𓮂������������Ă���
// 
// ================================================================

VersusCharacterPanelMove::VersusCharacterPanelMove()
{
	m_FramePanelImage.SetTexture("Assets/UI/CharacterBackPanel_Frame.png");

	SetSize(CVector2(147.0f, 320.0f) * 2.3f);

	m_FramePanelImage.m_IsVisible =
		m_BackPanelImage.m_IsVisible =
		m_CharacterImage.m_IsVisible = false;
}

VersusCharacterPanelMove::~VersusCharacterPanelMove()
{
}

void VersusCharacterPanelMove::Update()
{
	switch (m_state)
	{
	case VersusCharacterPanelMove::MOVESTATE::FADEIN:
		FadeInUpdate();
		break;
	case VersusCharacterPanelMove::MOVESTATE::MOVE:
		MoveUpdate();
		break;
	case VersusCharacterPanelMove::MOVESTATE::FADEOUT:
		FadeOutUpdate();
		break;
	}
}

void VersusCharacterPanelMove::Draw()
{
	m_BackPanelImage.Draw();
	m_CharacterImage.Draw();
	m_FramePanelImage.Draw();
}

void VersusCharacterPanelMove::SetPlayerNum(int playerNum)
{
	switch (playerNum)
	{
	case 1:	//��
		m_BackPanelImage.SetTexture("Assets/UI/CharacterBackPanel_Red.png");
		break;
	case 2:	//��
		m_BackPanelImage.SetTexture("Assets/UI/CharacterBackPanel_Blue.png");
		break;
	default:
		m_BackPanelImage.SetTexture("Assets/UI/CharacterBackPanel_Red.png");
		break;
	}
}

void VersusCharacterPanelMove::SetCharacter(SelectCharacterList::CHARACTER Character)
{
	m_CharacterImage.SetCharacterImage(Character);
}

void VersusCharacterPanelMove::FadeInUpdate()
{
	m_CountTime += 1.0f / 60.0f;

	float Percent = m_CountTime / m_FadeInTime;

	if (m_CountTime > m_FadeInTime)
	{
		Percent = 1.0f;
		m_CountTime = 0.0f;
		m_state = VersusCharacterPanelMove::MOVESTATE::MOVE;
	}

	SetColor(DirectX::XMFLOAT4(Percent, Percent, Percent, Percent));

	CVector3 DrawPos = (m_FadeStartPos * (1.0f - Percent)) + (m_MoveStartPos * Percent);
	SetPos(DrawPos);
}

void VersusCharacterPanelMove::MoveUpdate()
{
	m_CountTime += 1.0f / 60.0f;

	float Percent = m_CountTime / m_MoveTime;

	if (m_CountTime > m_MoveTime)
	{
		Percent = 1.0f;
		m_CountTime = 0.0f;
		m_state = VersusCharacterPanelMove::MOVESTATE::FADEOUT;
	}


	CVector3 DrawPos = (m_MoveStartPos * (1.0f - Percent)) + (m_MoveEndPos * Percent);
	SetPos(DrawPos);
}

void VersusCharacterPanelMove::FadeOutUpdate()
{
	m_CountTime += 1.0f / 60.0f;

	float Percent = m_CountTime / m_FadeOutTime;

	if (m_CountTime > m_FadeOutTime)
	{
		Percent = 1.0f;
		m_CountTime = 0.0f;
		m_state = VersusCharacterPanelMove::MOVESTATE::MAX;
	}

	SetColor(DirectX::XMFLOAT4(1.0f - Percent, 1.0f - Percent, 1.0f - Percent, 1.0f - Percent));

	CVector3 DrawPos = (m_MoveEndPos * (1.0f - Percent)) + (m_FadeEndPos * Percent);
	SetPos(DrawPos);
}
