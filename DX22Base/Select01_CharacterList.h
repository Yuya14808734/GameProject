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
	SelectCharacterList();
	~SelectCharacterList();
	void Draw();	//キャラクターを描画する
	std::array<Image2D, static_cast<int>(CHARACTER::MAX)>& GetCharacterStandImageList();
	std::array<Image2D, static_cast<int>(CHARACTER::MAX)>& GetCharacterIconImageList();
	std::array <CVector3, static_cast<int>(CHARACTER::MAX)>& GetIconPos();
	CVector2& GetIconSize();

private:
	std::array <Image2D, static_cast<int>(CHARACTER::MAX)> m_CharacterStandImages;
	std::array <Image2D, static_cast<int>(CHARACTER::MAX)> m_CharacterIconImages;
	std::array <CVector3, static_cast<int>(CHARACTER::MAX)> m_CharacterIconPos;		//アイコンの位置
	CVector2 m_CharacterIconSize;	//アイコンのサイズ

};