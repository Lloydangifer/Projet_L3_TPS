#include "CShTPSEnemy.h"


CShTPSEnemy::CShTPSEnemy(void)
{
	CShTPSCharacter::CShTPSCharacter();
	m_CurrentState = e_state_idle;
	m_Target = m_Position;
}

void CShTPSEnemy::Initialize(const CShIdentifier & levelIdentifier, CShTPSGun * defaultGun,ShEntity2 * sprite, CShString enemyCharacterControlleridentifier)
{
	m_pSprite = sprite;
	SH_ASSERT(shNULL != m_pSprite);

	CShTPSCharacter::Initialize(levelIdentifier,defaultGun);

	// Initialize the character controller with the level, the identifier, the position, the radius, the direction, the speed.
	ShCharacterController *	pCharacterController = shNULL;
	pCharacterController = ShCharacterController::Create(levelIdentifier, CShIdentifier(enemyCharacterControlleridentifier), m_Position, 25.0, m_Direction, m_Speed);
	m_pCharacterController = pCharacterController;
	SH_ASSERT(shNULL != m_pCharacterController);
}

void CShTPSEnemy::Update(void)
{
	if(m_Position != m_Target) // If the enemy is not on its target's location, he will go, else he will stay
	{
		m_CurrentState = e_state_attack;
	}
	else
	{
		m_CurrentState = e_state_idle;
	}

	switch(m_CurrentState)
	{
		case e_state_idle:
			break;
		case e_state_attack:
			break;
	}
}

void CShTPSEnemy::SetTarget(CShVector2 target)
{
	m_Target = target;
}

CShVector2 CShTPSEnemy::GetTarget(void)
{
	return m_Target;
}