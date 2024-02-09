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
		NormalVelocityVector.cross(NormalChangeVector).normalize(),						//回す軸
		RotateRadian * m_pBlowAwayParameter->VectorChangePower				//回す弧度
	).RotateVector(NormalVelocityVector);											//回すベクトル

	m_pCharacterParameter->MoveVector = CVector3::GetZero();
}

void CharacterBase_BlowAwayState::Uninit()
{

}

void CharacterBase_BlowAwayState::Update()
{
	m_Count++;

	if (m_Count % 20)
	{
		//飛んでいるエフェクトを追加
		SingleSmoke* pSingleSmoke = new SingleSmoke();
		pSingleSmoke->PlayEffect(m_pCharacterParameter->Pos,1.0f);

		m_pGameScene->GetEffectVector()->push_back(pSingleSmoke);
	}

	//地面に当たっていなければ
	if (m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Down);
		return;
	}

	//吹っ飛ばされたベクトルをどんどん短くしていく
	m_pCharacterParameter->Velocity.x *= m_pBlowAwayParameter->SmashMitigation;

	//上から下に向かうベクトルに変わったら
	if (m_pCharacterParameter->Velocity.y > 0.0f)
	{
		m_pCharacterParameter->Velocity.y *= m_pBlowAwayParameter->SmashMitigation;
	}
	else
	{
		m_pCharacterParameter->Velocity.y += m_pJumpParameter->FallDownGravity;
	}
	
	float SmashNowLength = m_pCharacterParameter->Velocity.length();
	
	//ある程度短くなったら
	if (SmashNowLength < m_pBlowAwayParameter->MinimumSmashLength)
	{
		m_pCharacter->SetNextState(Character::STATE::State_FallDown);
	}

	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;
}