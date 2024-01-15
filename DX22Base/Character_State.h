#pragma once
#include "Character_Base.h"

class Character_State : public State
{
public:
	enum class TYPE
	{
		DEFAULT = 0,
		ATTACK,
		MAX
	};

public:
	Character_State(TYPE type) : m_StateType(type) {};
	Character_State() : Character_State(Character_State::TYPE::DEFAULT) {};
	virtual ~Character_State() {};

	Character_State::TYPE GetType();
	void SetCharacter(Character* pCharacter);
	void SetController(PlayerController* pController);
	void SetCharacterParameter(Character::CHARACTER_PARAMETER* pCharacterParameter);
	void SetStage(Stage* pStage);
	void SetModelDrawer(ModelDrawer* pModelDrawer);
	void SetCharacterCollider(BoxCollider* pCollider);
	void SetAttackCollider(std::vector<Character::ATTACKPARAM>* pAttackCollider);
	void SetMoveParameter(Character::MOVEPARAMETER* pMoveParameter);
	void SetJumpParameter(Character::JUMPPARAMETER* pJumpParameter);
	void SetBlowAwayParameter(Character::BLOWAWAYPARAMETER* pBlowAwayParameter);

public:
	virtual void Init() {};
	virtual void Uninit() {};
	virtual void Update() {};

private:
	Character_State::TYPE m_StateType = Character_State::TYPE::MAX;

protected:
	Character* m_pCharacter = nullptr;
	PlayerController* m_pController = nullptr;
	Character::CHARACTER_PARAMETER* m_pCharacterParameter = nullptr;
	Stage* m_pStage = nullptr;
	ModelDrawer* m_pModelDrawer = nullptr;
	BoxCollider* m_pCharacterCollider = nullptr;
	std::vector<Character::ATTACKPARAM>* m_pAttackCollider = nullptr;
	Character::MOVEPARAMETER* m_pMoveParameter = nullptr;
	Character::JUMPPARAMETER* m_pJumpParameter = nullptr;
	Character::BLOWAWAYPARAMETER* m_pBlowAwayParameter = nullptr;
};