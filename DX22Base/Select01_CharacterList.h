#pragma once
#include <array>
#include "Image2D.h"

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
	void Draw();	//�L�����N�^�[��`�悷��
	std::array<Image2D, static_cast<int>(CHARACTER::MAX)>& GetCharacterImageList();

private:
	std::array <Image2D, static_cast<int>(CHARACTER::MAX)> m_CharacterImages;

};