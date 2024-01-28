#pragma once
#include "Image2D.h"
#include "Select01_CharacterList.h"


class ShapeCutCharacterPanel : public Image2D
{
public:
	ShapeCutCharacterPanel();
	~ShapeCutCharacterPanel() override;
private:
	void PrevDraw() override;
public:
	void SetCharacterImage(SelectCharacterList::CHARACTER Character);
	void SetCharacterUVPos(const CVector2& pos);
	void SetCharacterUVScale(float Scale);

private:
	ID3D11ShaderResourceView* m_pCharacterImage = nullptr;		//�L�����N�^�[�̉摜
	ConstantBuffer* m_ConstantBuffer_SecondTextureUV = nullptr;	//�L�����N�^�[��UV����n��
	CVector2 m_UVPos_Character;									//�L�����N�^�[��UV�ʒu
	CVector2 m_BaseImageSize_Character;							//PNG�̉摜�̑傫��
	CVector2 m_UVSize_Character;								//��̑傫���ɑ΂��Ăǂꂭ�炢�������������̃T�C�Y
};

class VersusCharacterPanelMove
{
private:
	enum class MOVESTATE : int
	{
		FADEIN = 0,
		MOVE,
		FADEOUT,
		MAX,
	};

public:
	VersusCharacterPanelMove();
	~VersusCharacterPanelMove();
	void Update();
	void Draw();

	void SetPlayerNum(int playerNum);
	void SetCharacter(SelectCharacterList::CHARACTER Character);

private:
	void FadeInUpdate();
	void MoveUpdate();
	void FadeOutUpdate();


private:
	VersusCharacterPanelMove::MOVESTATE m_state = VersusCharacterPanelMove::MOVESTATE::MAX;

	Image2D					  m_BackPanelImage;		//�p�l���̖͗l�摜(���ɒu�����)
	Image2D					  m_FramePanelImage;	//�p�l���̃t���[���摜(���ɒu�����)
	ShapeCutCharacterPanel	  m_CharacterImage;		//�p�l���̃L�����N�^�[�摜(�O�ɒu�����)
	
	float m_CountTime = 0.0f;
	
	CVector3 m_FadeStartPos;
	CVector3 m_MoveStartPos;
	CVector3 m_MoveEndPos;
	CVector3 m_FadeEndPos;
	
	float m_MoveTime = 0.0f;
	float m_FadeInTime = 0.0f;
	float m_FadeOutTime = 0.0f;

public:
	//=======================================================
	// Set/Get�֐�
	//=======================================================
	void SetStartFade() {
		m_state = VersusCharacterPanelMove::MOVESTATE::FADEIN;
		m_FramePanelImage.m_IsVisible =
			m_BackPanelImage.m_IsVisible =
			m_CharacterImage.m_IsVisible = true;
	}

	void SetFadeTime(float FadeInTime, float MoveTime, float FadeOutTime)
	{
		m_FadeInTime = FadeInTime;
		m_MoveTime = MoveTime;
		m_FadeOutTime = FadeOutTime;
	}

	void SetFadePos(const CVector3& FadeStartPos, const CVector3& MoveStartPos, const CVector3& MoveEndPos, const CVector3& FadeEndPos)
	{
		m_FadeStartPos = FadeStartPos;
		m_MoveStartPos = MoveStartPos;
		m_MoveEndPos = MoveEndPos;
		m_FadeEndPos = FadeEndPos;
	}

	void SetPos(const CVector3& pos) {
		m_BackPanelImage.m_pos =
			m_FramePanelImage.m_pos =
			m_CharacterImage.m_pos = pos;
	}

	void SetSize(const CVector2& size) { 
		m_BackPanelImage.m_size = 
			m_FramePanelImage.m_size =
			m_CharacterImage.m_size = size; 
		m_FramePanelImage.m_size.x += 5.0f;
		m_FramePanelImage.m_size.y += 5.0f;
	}

	void SetColor(const DirectX::XMFLOAT4& color) {
		m_BackPanelImage.m_color =
			m_FramePanelImage.m_color =
			m_CharacterImage.m_color = color;
	}

};