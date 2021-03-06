#include "CShTPSPlayer.h"

CShTPSPlayer::CShTPSPlayer(void)
: CShTPSCharacter()
{
}

void CShTPSPlayer::Initialize(const CShIdentifier & levelIdentifier, CShTPSGun * defaultGun)
{
	if (!m_bInitialized)
	{
		m_bInitialized  = true;

		// Load a sprite in 2D in the Sprite attribute
		m_pSprite = shNULL;
		m_pSprite = ShEntity2::Find(levelIdentifier, CShIdentifier(PLAYER_SPRITE_NAME));
		float radius = CHARACTER_CONTROLLER_RADIUS_2D; // radius for the character controller
	
		if (shNULL == m_pSprite) // if no player sprite is on the map, one is created for 3D, to manage collision between invisible 2D stuff
		{
			m_pSprite = ShEntity2::Create(levelIdentifier, CShIdentifier("player_sprite_forced_2D"), GID(layer_default), CShIdentifier("tps"), CShIdentifier("player"), CShVector3(0.0f,0.0f,1.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));

		}

		SH_ASSERT(shNULL != m_pSprite);
		m_pModel = shNULL;
		m_pModel = ShEntity3::Find(levelIdentifier, CShIdentifier(PLAYER_SPRITE_NAME));
		if(shNULL != m_pModel)
		{
			m_3d = true;
			m_pAnimIdle = ShAnimation::Find(CShIdentifier(PLAYER_ANIM_IDLE));
			SH_ASSERT(shNULL != m_pAnimIdle);
			m_pAnimRun = ShAnimation::Find(CShIdentifier(PLAYER_ANIM_RUN));
			SH_ASSERT(shNULL != m_pAnimRun);
			/*m_pAnimAttack = ShAnimation::Find(CShIdentifier(PLAYER_ANIM_ATTACK));
			SH_ASSERT(shNULL != m_pAnimAttack);*/
			ShEntity3::AnimationPlay(m_pModel, m_pAnimIdle,true);
			radius= CHARACTER_CONTROLLER_RADIUS_3D;	
		}
		else
		{
			m_3d = false;
		}

		if(m_3d)
		{
			ShObject::SetShow(m_pSprite, false);
			ShObject::SetShow(m_pModel, true);
		}
		else
		{
			ShObject::SetShow(m_pSprite, true);
		}
		CShTPSCharacter::Initialize(levelIdentifier, CShIdentifier(PLAYER_SPRITE_NAME), defaultGun);

		// Initialize the character controller with the level, the identifier, the position, the radius, the direction, the speed.
		ShCharacterController *	pCharacterController = shNULL;
		pCharacterController = ShCharacterController::Create(levelIdentifier, CShIdentifier("character_controller_character_001"), m_Position, radius, m_Direction, m_Speed);
		m_pCharacterController = pCharacterController;
		SH_ASSERT(shNULL != m_pCharacterController);
	}
	else
	{
		Spawn();
	}
}

void CShTPSPlayer::SwitchToAnimationRun(void)
{
	if(m_3d)
	{
		ShEntity3::AnimationPlay(m_pModel, m_pAnimRun,true);
	}
}

void CShTPSPlayer::SwitchToAnimationIdle(void)
{
	if(m_3d)
	{
		ShEntity3::AnimationPlay(m_pModel, m_pAnimIdle,true);
	}
}

void CShTPSPlayer::SwitchToAnimationAttack(void)
{
	if(m_3d)
	{
		ShEntity3::AnimationPlay(m_pModel, m_pAnimRun,true); // TODO change to attack animation if it ever works
	}
}