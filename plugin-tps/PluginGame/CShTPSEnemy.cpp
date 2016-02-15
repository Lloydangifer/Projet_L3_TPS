#include "CShTPSEnemy.h"


CShTPSEnemy::CShTPSEnemy(void)
{
	CShTPSCharacter::CShTPSCharacter();
	m_CurrentState = e_state_idle;
	m_Target = m_Position;
	m_Speed = 75.0f;
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

	m_Target = m_Position;
}

void CShTPSEnemy::Update(float dt)
{
	if(m_Position != m_Target) // If the enemy is not on its target's location, he will go, else he will stay
	{
		m_CurrentState = e_state_attack;
		float length = CShVector2(m_Target - m_Position).GetLength();
		m_Direction = CShVector2((m_Target.m_x - m_Position.m_x)/length , (m_Target.m_y - m_Position.m_y)/length);
		ShCharacterController::SetWalkDirection(m_pCharacterController, m_Direction);
		ShCharacterController::SetWalkSpeed(m_pCharacterController, m_Speed);
	}
	else
	{
		m_CurrentState = e_state_idle;
	}

	switch(m_CurrentState)
	{
		case e_state_idle:
				ShCharacterController::SetWalkSpeed(m_pCharacterController, 0.0f);
			break;
		case e_state_attack:
			ShCharacterController::Update(m_pCharacterController);
			m_Position = ShCharacterController::GetPosition(m_pCharacterController);
			ShEntity2::SetPositionX(m_pSprite,m_Position.m_x);
			ShEntity2::SetPositionY(m_pSprite,m_Position.m_y);
			//ShEntity2::SetRotation(m_pSprite, CShEulerAngles(0.0f, 0.0f, shAcosf(m_Direction.m_x/m_Direction.m_y)));
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