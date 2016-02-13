#include "CShTPSEnemy.h"

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