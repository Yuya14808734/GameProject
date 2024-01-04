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
	void Draw();	//キャラクターを描画する
	
	std::array <CVector3, static_cast<int>(CHARACTER::MAX)>& GetIconPos();
	CVector2& GetIconSize();

private:
	std::array <CVector3, static_cast<int>(CHARACTER::MAX)> m_CharacterIconPos;		//アイコンの位置
	CVector2 m_CharacterIconSize;	//アイコンのサイズ
	Image2D m_IconBackImage;
	Image2D m_IconFrameImage;
};