#pragma once
#include <array>
#include "Image2D.h"
#include "Calculation.h"

class SelectCharacterList
{
public:
	enum class CHARACTER : int
	{
		UNITYCHAN = 0,
		MAX
	};

public:
	static void LoadTexture();
	static void ReleaseTexture();
	static std::array<Image2D, static_cast<int>(CHARACTER::MAX)>& GetCharacterStandImageList();
	static std::array<Image2D, static_cast<int>(CHARACTER::MAX)>& GetCharacterIconImageList();

private:
	static bool m_CharacterImageLoad;
	static std::array <Image2D, static_cast<int>(CHARACTER::MAX)> m_CharacterStandImages;
	static std::array <Image2D, static_cast<int>(CHARACTER::MAX)> m_CharacterIconImages;

public:
	SelectCharacterList();
	~SelectCharacterList();
	void Draw();	//�L�����N�^�[��`�悷��
	
	std::array <CVector3, static_cast<int>(CHARACTER::MAX)>& GetIconPos();
	CVector2& GetIconSize();

private:
	std::array <CVector3, static_cast<int>(CHARACTER::MAX)> m_CharacterIconPos;		//�A�C�R���̈ʒu
	CVector2 m_CharacterIconSize;	//�A�C�R���̃T�C�Y
	Image2D m_IconBackImage;
	Image2D m_IconFrameImage;
};