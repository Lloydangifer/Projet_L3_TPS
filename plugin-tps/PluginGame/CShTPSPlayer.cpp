#include "CShTPSPlayer.h"



void CShTPSPlayer::Initialize(const CShIdentifier & levelIdentifier, CShTPSGun * defaultGun)
{
	// Load a sprite in 2D in the Sprite attribute
	m_pSprite = ShEntity2::Find(levelIdentifier, CShIdentifier(PLAYER_SPRITE_NAME));
	float radius = CHARACTER_CONTROLLER_RADIUS_2D; // radius for the character controller
	// If the game don't find a 2D Sprite, it search for a 3D model
	if(shNULL == m_pSprite)
	{
		m_pSprite = ShEntity3::Find(levelIdentifier, CShIdentifier(PLAYER_SPRITE_NAME));
		m_pAnimIdle = ShAnimation::Find(CShIdentifier(PLAYER_ANIM_IDLE));
		SH_ASSERT(shNULL != m_pAnimIdle);
		m_pAnimRun = ShAnimation::Find(CShIdentifier(PLAYER_ANIM_RUN));
		SH_ASSERT(shNULL != m_pAnimRun);
		/*m_pAnimAttack = ShAnimation::Find(CShIdentifier(PLAYER_ANIM_ATTACK));
		SH_ASSERT(shNULL != m_pAnimAttack);*/
		ShEntity3::AnimationPlay((ShEntity3 *)m_pSprite, m_pAnimIdle,true);
		radius= CHARACTER_CONTROLLER_RADIUS_3D;
		m_3d = true;
	}
	SH_ASSERT(shNULL != m_pSprite);

	ShObject::SetShow(m_pSprite, true);
	
	CShTPSCharacter::Initialize(levelIdentifier,defaultGun);

	// Initialize the character controller with the level, the identifier, the position, the radius, the direction, the speed.
	ShCharacterController *	pCharacterController = shNULL;
	pCharacterController = ShCharacterController::Create(levelIdentifier, CShIdentifier("character_controller_character_001"), m_Position, radius, m_Direction, m_Speed);
	m_pCharacterController = pCharacterController;
	SH_ASSERT(shNULL != m_pCharacterController);
}


void CShTPSPlayer::SwitchToAnimationRun(void)
{
	if(m_3d)
	{
		ShEntity3::AnimationPlay((ShEntity3 *)m_pSprite, m_pAnimRun,true);
	}
}

void CShTPSPlayer::SwitchToAnimationIdle(void)
{
	if(m_3d)
	{
		ShEntity3::AnimationPlay((ShEntity3 *)m_pSprite, m_pAnimIdle,true);
	}
}

void CShTPSPlayer::SwitchToAnimationAttack(void)
{
	if(m_3d)
	{
		ShEntity3::AnimationPlay((ShEntity3 *)m_pSprite, m_pAnimRun,true); // TODO change to attack animation if it ever works
	}
}
