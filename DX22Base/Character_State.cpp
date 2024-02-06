#include "Character_State.h"

Character_State::TYPE Character_State::GetType()
{
	return m_StateType;
}

void Character_State::SetCharacter(Character* pCharacter)
{
	m_pCharacter = pCharacter;
}

void Character_State::SetController(PlayerController* pController)
{
	m_pController = pController;
}
void Character_State::SetCharacterParameter(Character::CHARACTER_PARAMETER* pCharacterParameter)
{
	m_pCharacterParameter = pCharacterParameter;
}

void Character_State::SetStage(Stage* pStage)
{
	m_pStage = pStage;
}

void Character_State::SetModelDrawer(ModelDrawer * pModelDrawer)
{
	m_pModelDrawer = pModelDrawer;
}

void Character_State::SetCharacterCollider(BoxCollider* pCollider)
{
	m_pCharacterCollider = pCollider;
}

void Character_State::SetAttackCollider(std::vector<Character::ATTACKPARAM>* pAttackCollider)
{
	m_pAttackCollider = pAttackCollider;
}

void Character_State::SetMoveParameter(Character::MOVEPARAMETER * pMoveParameter)
{
	m_pMoveParameter = pMoveParameter;
}

void Character_State::SetJumpParameter(Character::JUMPPARAMETER * pJumpParameter)
{
	m_pJumpParameter = pJumpParameter;
}

void Character_State::SetBlowAwayParameter(Character::BLOWAWAYPARAMETER * pBlowAwayParameter)
{
	m_pBlowAwayParameter = pBlowAwayParameter;
}

