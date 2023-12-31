#include "Select01_CharacterList.h"

SelectCharacterList::SelectCharacterList()
{
	const char* CharacterImageFilePath[static_cast<int>(CHARACTER::MAX)] =
	{
		"Assets/CharacterImage/SelectCharacter_UnityChan.png",
	};

	const char* CharacterIconImageFilePath[static_cast<int>(CHARACTER::MAX)] =
	{
		"Assets/CharacterImage/UnitychanIcon.png",
	};

	//描画するときの最初の位置
	CVector3 BasePos = CVector3(640.0f,300.0f,0.0f);
	CVector2 ImageSize = CVector2(273.0f, 400.0f) * 0.8f;
	CVector3 BaseDistance = CVector3(10.0f,0.0f,0.0f);

	//各画像の位置の設定
	for (int i = 0;i < static_cast<int>(CHARACTER::MAX);i++)
	{
		//キャラクターの立ち絵画像
		m_CharacterImages[i].SetTexture(CharacterImageFilePath[i]);
		m_CharacterImages[i].m_pos =
			BasePos + ((BaseDistance + ImageSize) * static_cast<float>(i));
		m_CharacterImages[i].m_size = ImageSize;

		//キャラクターのアイコンの画像
		m_CharacterIconImages[i].SetTexture(CharacterIconImageFilePath[i]);
		m_CharacterIconImages[i].m_size = CVector2(150.0f, 150.0f);

	}
}

SelectCharacterList::~SelectCharacterList()
{

}

void SelectCharacterList::Draw()
{
	//各画像の位置の設定
	for (int i = 0; i < static_cast<int>(CHARACTER::MAX); i++)
	{
		m_CharacterImages[i].Draw();
	}
}

std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>& SelectCharacterList::GetCharacterImageList()
{
	return m_CharacterImages;
}

std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>& SelectCharacterList::GetCharacterIconImageList()
{
	return m_CharacterIconImages;
}
