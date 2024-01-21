// ====================================================================================
// インクルード
// ====================================================================================

#include "Select01_CharacterList.h"
#include "Input.h"


// ====================================================================================
// static
// ====================================================================================

bool SelectCharacterList::m_CharacterImageLoad = false;
std::array <Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)> SelectCharacterList::m_CharacterStandImages;
std::array <Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)> SelectCharacterList::m_CharacterIconImages;

void SelectCharacterList::LoadTexture()
{
	if (m_CharacterImageLoad)
	{
		return;
	}

	m_CharacterImageLoad = true;

	const char* CharacterImageFilePath[static_cast<int>(CHARACTER::MAX)] =
	{
		"Assets/CharacterImage/StandImage_UnityChan.png",
	};

	const char* CharacterIconImageFilePath[static_cast<int>(CHARACTER::MAX)] =
	{
		"Assets/CharacterImage/IconImage_UnityChan.png",
	};

	//各画像の位置の設定
	for (int i = 0; i < static_cast<int>(CHARACTER::MAX); i++)
	{
		//キャラクターの立ち絵画像の読み込み
		m_CharacterStandImages[i].SetTexture(CharacterImageFilePath[i]);

		//キャラクターのアイコンの画像の読み込み
		m_CharacterIconImages[i].SetTexture(CharacterIconImageFilePath[i]);
	}
}

void SelectCharacterList::ReleaseTexture()
{
	if(!m_CharacterImageLoad)
	{
		return;
	}

	m_CharacterImageLoad = false;

	//各画像の位置の設定
	for (int i = 0; i < static_cast<int>(CHARACTER::MAX); i++)
	{
		//キャラクターの立ち絵画像のメモリ解放
		m_CharacterStandImages[i].ReleaseTexture();

		//キャラクターのアイコンの画像のメモリ解放
		m_CharacterIconImages[i].ReleaseTexture();
	}
}

std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>& SelectCharacterList::GetCharacterStandImageList()
{
	return m_CharacterStandImages;
}

std::array<Image2D, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>& SelectCharacterList::GetCharacterIconImageList()
{
	return m_CharacterIconImages;
}

// ====================================================================================
// dynamic
// ====================================================================================

SelectCharacterList::SelectCharacterList()
{
	const CVector3 IconPos[static_cast<int>(CHARACTER::MAX)] =
	{
		CVector3(640.0f, 280.0f, 0.0f),
	};

	m_CharacterIconSize = CVector2(200.0f, 200.0f) * 0.8f;

	for (int i = 0; i < static_cast<int>(CHARACTER::MAX); i++) 
	{
		m_CharacterIconPos[i] = IconPos[i];
	}

	m_IconBackImage.SetTexture("Assets/UI/IconbackImage.png");
	m_IconBackImage.m_size = m_CharacterIconSize;
	m_IconFrameImage.SetTexture("Assets/UI/SelectFrame.png");
	m_IconFrameImage.m_size = m_CharacterIconSize * 1.01f;
	m_IconFrameImage.m_color = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
}

SelectCharacterList::~SelectCharacterList()
{

}

void SelectCharacterList::Draw()
{
	//各画像の位置の設定
	for (int i = 0; i < static_cast<int>(CHARACTER::MAX); i++)
	{
		m_IconBackImage.m_pos = m_CharacterIconPos[i];
		m_IconFrameImage.m_pos = m_CharacterIconPos[i];
		m_CharacterIconImages[i].m_BasePos = CVector3::GetZero();
		m_CharacterIconImages[i].m_pos = m_CharacterIconPos[i];
		m_CharacterIconImages[i].m_size = m_CharacterIconSize;

		m_IconBackImage.Draw();
		m_CharacterIconImages[i].Draw();
		m_IconFrameImage.Draw();
	}
}

std::array<CVector3, static_cast<int>(SelectCharacterList::CHARACTER::MAX)>& SelectCharacterList::GetIconPos()
{
	return m_CharacterIconPos;
}

CVector2& SelectCharacterList::GetIconSize()
{
	return m_CharacterIconSize;
}
