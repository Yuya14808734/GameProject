#include "Select01_CharacterList.h"

SelectCharacterList::SelectCharacterList()
{
	const char* CharacterImageFilePath[static_cast<int>(CHARACTER::MAX)] =
	{
		"Assets/CharacterImage/SelectCharacter_UnityChan.png"
	};

	//描画するときの最初の位置
	CVector3 BasePos = CVector3(640.0f,300.0f,0.0f);
	CVector2 ImageSize = CVector2(273.0f, 400.0f) * 0.8f;
	CVector3 BaseDistance = CVector3(10.0f,0.0f,0.0f);

	//各画像の位置の設定
	for (int i = 0;i < static_cast<int>(CHARACTER::MAX);i++)
	{
		m_CharacterImages[i].SetTexture(CharacterImageFilePath[i]);
		m_CharacterImages[i].m_pos =
			BasePos + ((BaseDistance + ImageSize) * static_cast<float>(i));
		m_CharacterImages[i].m_size = ImageSize;
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
