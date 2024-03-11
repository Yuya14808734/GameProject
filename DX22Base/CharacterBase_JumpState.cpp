#include "CharacterBase_JumpState.h"

void CharacterBase_JumpState::Init()
{
	if (m_pCharacterParameter->JumpCount == 0)
	{
		//最初のジャンプだった場合
		m_pCharacterParameter->Velocity.y = m_pJumpParameter->FirstJumpPower;
	}
	else
	{
		//二回目のジャンプだった場合
		m_pCharacterParameter->Velocity.y = m_pJumpParameter->SecondJumpPower;
	}

	m_pCharacterParameter->MoveVector = CVector3::GetZero();
	m_pCharacterParameter->JumpCount++;
}

void CharacterBase_JumpState::Uninit()
{

}

void CharacterBase_JumpState::Update()
{
	if (m_pCharacterParameter->HitGround)
	{
		m_pCharacter->SetNextState(Character::STATE::State_Idle);		
	}


	bool OnButton = false;

	m_pCharacterParameter->MoveVector.x =  
		m_pController->GetMoveInput().x * m_pMoveParameter->AirSideMoveSpeed;

	m_pCharacterParameter->Velocity.x *= m_pMoveParameter->AirDrag;	//空気抵抗を掛ける

	//もう一度ジャンプができる
	if (m_pCharacterParameter->JumpCount < m_pJumpParameter->MaxJumpCount)
	{
		if (m_pController->GetJumpTrigger())
		{
			m_pCharacter->SetNextState(Character::STATE::State_Jump);
		}
	}

	//攻撃
	if (m_pController->GetAttack())
	{
		m_pCharacter->SetNextState(Character::STATE::State_AttackAirN); //弱の設定
	}

	m_pCharacterParameter->Velocity.y 
		*= m_pJumpParameter->JumpUpReduction;		//1より小さい数値を掛ける

	//重力制御(最高の落下速度になったら)(一応の処理)
	if (m_pCharacterParameter->Velocity.y < m_pJumpParameter->DefaultFallSpeed)
	{
		m_pCharacterParameter->Velocity.y = m_pJumpParameter->DefaultFallSpeed;
	}

	//落下し始めたら
	if (m_pCharacterParameter->Velocity.y < m_pJumpParameter->ChangeFallSpeed)
	{
		m_pCharacter->SetNextState(Character::STATE::State_AirMove);
	}

	m_pCharacterParameter->Pos += m_pCharacterParameter->MoveVector;
	m_pCharacterParameter->Pos += m_pCharacterParameter->Velocity;

	//ジャンプした後の位置が天井を超えていたら戻してやる
	if (m_pCharacterParameter->Pos.y > m_pStage->GetDeadLineTopY())
	{
		m_pCharacterParameter->Pos.y = m_pStage->GetDeadLineTopY();
	}
}