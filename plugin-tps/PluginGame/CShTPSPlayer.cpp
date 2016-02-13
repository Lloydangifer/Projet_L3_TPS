#include "CShTPSPlayer.h"



void CShTPSPlayer::Initialize(const CShIdentifier & levelIdentifier, CShTPSGun * defaultGun)
{
	m_pSprite = ShEntity2::Find(levelIdentifier, CShIdentifier("sprite_tps_player"));
	SH_ASSERT(shNULL != m_pSprite);

	CShTPSCharacter::Initialize(levelIdentifier,defaultGun);

	// Initialize the character controller with the level, the identifier, the position, the radius, the direction, the speed.
	ShCharacterController *	pCharacterController = shNULL;
	pCharacterController = ShCharacterController::Create(levelIdentifier, CShIdentifier("character_controller_character_001"), m_Position, 25.0, m_Direction, m_Speed);
	m_pCharacterController = pCharacterController;
	SH_ASSERT(shNULL != m_pCharacterController);
}