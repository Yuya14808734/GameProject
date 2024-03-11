#include "CharacterBase_BlowAwayState.h"
#include "Input.h"
#include "XboxKeyboard.h"
#include "Effect01_SingleSmoke.h"

//===========================================================
//キャラクターが吹っ飛んでいるときの処理を書く
//
//===========================================================


void CharacterBase_BlowAwayState::Init()
{
	//ゲームシーンの設定
	m_pGameScene = static_cast<SceneGame*>(CScene::GetScene());
	m_Count = 0;

	//コントローラーの今入力されている左スティックのベクトルを取得する
	CVector3 ChangeVector = m_pController->GetLeftInputVector();

	//ベクトルを正規化して保存
	CVector3 NormalChangeVector = ChangeVector.normalize();
	NormalChangeVector.z = 0.0f;
	CVector3 NormalVelocityVector = m_pCharacterParameter->Velocity.normalize();
	NormalVelocityVector.z = 0.0f;

	//今飛ばされているベクトルとコントローラーで入力されたベクトルへ
	//数パーセント回す
	float RotateRadian = acosf(NormalVelocityVector.dot(NormalChangeVector));

	m_pCharacterParameter->Velocity = CQuaternion::RadianAxis(
		NormalVelocityVector.cross(NormalChangeVector).normalize(),					//回す軸
		RotateRadian * m_pBlowAwayParameter->VectorChangePower						//回す弧度
	).RotateVector(m_pCharacterParameter->Velocity);											//回すベクトル

	m_pCharacterParameter->MoveVector = CVector3::GetZero();

	//エフェクトの追加
	m_pMultipleSmoke = new MultipleSmoke();
	m_pMultipleSmoke->SetSingleSmokeEndTime(1.0f);
	m_pGameScene->GetEffectVector()->push_back(m_pMultipleSmoke);
}

void CharacterBase_BlowAwayState::Uninit()
{
	m_pMultipleSmoke->SetEffectAddEnd(true);
}

void CharacterBase_BlowAwayState::Update()
{
	m_Count++;

	if (m_Count % 2 == 0)
	{
		//飛んでいるエフェクトを追加
		m_pMultipleSmoke->AddPlayEffect(m_pCharacterParameter->Pos + CVector3(0.0f,0.5f,0.0f),
			m_pCharacterParameter->Velocity * -0.5f);
	}

	//地面に当たっていなければ
	if (m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Down);
		return;
	}

	//吹っ飛ばされたベクトルをどんどん短くしていく
	m_pCharacterParameter->Velocity *= m_pBlowAwayParameter->SmashMitigation;
	
	float SmashNowLength = m_pCharacterParameter->Velocity.length();
	
	//ある程度短くなったら
	if (SmashNowLength < m_pBlowAwayParameter->MinimumSmashLength)
	{
		m_pCharacter->SetNextState(Character::STATE::State_FallDown);
	}

	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
}