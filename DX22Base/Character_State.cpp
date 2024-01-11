#include "Character_Base.h"

Character_State::TYPE Character_State::GetType()
{
	return m_StateType;
}

void Character_State::SetCharacter(Character* pCharacter)
{

}

void Character_State::SetController(PlayerController* pController)
{

}
void Character_State::SetCharacterParameter(Character::CHARACTER_PARAMETER* CharacterParameter)
{

}

void Character_State::SetStage(Stage* pStage)
{

}

void Character_State::SetCharacterCollider(BoxCollider* pCollider)
{

}

void Character_State::SetAttackCollider(std::vector<Character::ATTACKPARAM>* pAttackCollider)
{

}
