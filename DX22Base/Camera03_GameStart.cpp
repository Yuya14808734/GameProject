#include "Camera03_GameStart.h"

void CameraGameStart::Init()
{
	m_pos = m_StartPos;
	m_Time = 0.0f;
	m_NowLookCharacterNum = 0;
}

void CameraGameStart::Uninit()
{
	m_CharacterPos.clear();
}

void CameraGameStart::Update()
{
	m_Time += 1.0f / 60.0f;

	float NowRange = m_Time / m_CharacterLerpTime;

	NowRange = NowRange >= 1.0f ? 1.0f : NowRange;

	m_pos = m_StartPos * (1.0f - NowRange) + m_EndPos * NowRange;
	m_look = m_pos;
	m_look.z = 0.0f;

	if (m_NowLookCharacterNum + 2 != m_CharacterPos.size())
	{
		//移動する時間とキャラクターを見る時間を超えたら
		if (m_Time >= m_CharacterLookTime + m_CharacterLerpTime)
		{
			m_Time = 0.0f;
			m_NowLookCharacterNum++;
			m_StartPos = m_CharacterPos[m_NowLookCharacterNum];
			m_EndPos = m_CharacterPos[m_NowLookCharacterNum + 1];
		}
	}
}

void CameraGameStart::ChangeInit()
{

}

void CameraGameStart::ChangeUninit()
{
	
}

void CameraGameStart::SetCharacter(std::vector<Character*>& pCharacterVector)
{
	m_CharacterPos.clear();

	m_CharacterPos.push_back(pCharacterVector[0]->GetPos());

	//各キャラクターの位置を設定
	for (Character* copy : pCharacterVector)
	{
		CVector3 CameraPos = copy->GetPos();
		CameraPos.y += 1.0f;
		CameraPos.z = -3.0f;
		m_CharacterPos.push_back(CameraPos);
	}

	//最後の位置を設定
	m_CharacterPos.push_back(CVector3(0.0f, 3.0f, -20.0f));

	m_StartPos = m_CharacterPos[m_NowLookCharacterNum];
	m_EndPos = m_CharacterPos[m_NowLookCharacterNum + 1];

}


