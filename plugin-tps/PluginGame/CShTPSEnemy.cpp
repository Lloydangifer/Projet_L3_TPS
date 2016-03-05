#include "CShTPSEnemy.h"


CShTPSEnemy::CShTPSEnemy(void)
{
	CShTPSCharacter::CShTPSCharacter();
	m_CurrentState = e_state_idle;
	m_Target = m_Position;
	m_Speed = 75.0f;
}

void CShTPSEnemy::Initialize(const CShIdentifier & levelIdentifier, CShTPSGun * defaultGun,ShObject * sprite, CShString enemyCharacterControlleridentifier)
{
	m_pSprite = sprite;
	SH_ASSERT(shNULL != m_pSprite);
	ShObject::SetShow(m_pSprite, true);
	float radius = CHARACTER_CONTROLLER_RADIUS_2D;

	if(ShObject::e_type_entity3 == ShObject::GetType(m_pSprite))
	{
		m_3d = true;
		m_pAnimIdle = ShAnimation::Find(CShIdentifier(ENEMY_ANIM_IDLE));
		SH_ASSERT(shNULL != m_pAnimIdle);
		m_pAnimRun = ShAnimation::Find(CShIdentifier(ENEMY_ANIM_RUN));
		SH_ASSERT(shNULL != m_pAnimRun);
		/*m_pAnimAttack = ShAnimation::Find(CShIdentifier(ENEMY_ANIM_ATTACK));
		SH_ASSERT(shNULL != m_pAnimAttack);*/
		ShEntity3::AnimationPlay((ShEntity3 *)m_pSprite, m_pAnimIdle,true);
		radius= CHARACTER_CONTROLLER_RADIUS_3D;
	}

	CShTPSCharacter::Initialize(levelIdentifier,defaultGun);

	// Initialize the character controller with the level, the identifier, the position, the radius, the direction, the speed.
	ShCharacterController *	pCharacterController = shNULL;
	pCharacterController = ShCharacterController::Create(levelIdentifier, CShIdentifier(enemyCharacterControlleridentifier), m_Position, radius, m_Direction, m_Speed);
	m_pCharacterController = pCharacterController;
	SH_ASSERT(shNULL != m_pCharacterController);

	m_Target = m_Position;
}

void CShTPSEnemy::Update(float dt)
{
	if(m_pGun->GetCoolDown() < m_pGun->GetFireRate())
	{
		m_pGun->AddToCoolDown(dt);
	}

	if(HasReachedTarget()) // If the enemy is on its target's location, he will go, else he will stay
	{
		m_CurrentState = e_state_idle;
	}
	else
	{
		m_CurrentState = e_state_attack;
		float length = CShVector2(m_Target - m_Position).GetLength();
		m_Direction = CShVector2((m_Target.m_x - m_Position.m_x)/length , (m_Target.m_y - m_Position.m_y)/length);
		ShCharacterController::SetWalkDirection(m_pCharacterController, m_Direction);
		ShCharacterController::SetWalkSpeed(m_pCharacterController, m_Speed);
	}

	switch(m_CurrentState)
	{
		case e_state_idle:
			ShCharacterController::SetWalkSpeed(m_pCharacterController, 0.0f);
			if(m_3d)
			{
				ShEntity3::AnimationPlay((ShEntity3 *)m_pSprite, m_pAnimIdle,true);
			}
			break;
		case e_state_attack:

			m_Position = ShCharacterController::GetPosition(m_pCharacterController);
			ShObject::SetPositionX(m_pSprite,m_Position.m_x);
			ShObject::SetPositionY(m_pSprite,m_Position.m_y);
			if(m_3d)
			{
				ShEntity3::AnimationPlay((ShEntity3 *)m_pSprite, m_pAnimRun,true); //TODO changer animation en attaque si ça marche un jour
				ShEntity3::SetRotation(m_pSprite, CShEulerAngles(0.0f, 0.0f, std::atan2(m_Direction.m_y,m_Direction.m_x ) + 1.5f )); // 1.5f : valeur piffée pour que les enemis regardent bien le joueur
			}
			//ShEntity2::SetRotation(m_pSprite, CShEulerAngles(0.0f, 0.0f, shAcosf(m_Direction.m_x/m_Direction.m_y)));
			break;
	}
	ShCharacterController::Update(m_pCharacterController);
}

void CShTPSEnemy::SetTarget(CShVector2 target)
{
	m_Target = target;
}

CShVector2 CShTPSEnemy::GetTarget(void)
{
	return m_Target;
}

EState CShTPSEnemy::GetCurrentState()
{
	return m_CurrentState;
}


bool CShTPSEnemy::HasReachedTarget(void)
{
	if (std::abs(m_Target.m_x - m_Position.m_x) < 10.0f
		&& std::abs(m_Target.m_y - m_Position.m_y) < 10.0f)
	{
		return true;
	}

	return false;
}