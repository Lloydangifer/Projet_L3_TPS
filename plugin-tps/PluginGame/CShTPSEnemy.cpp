#include "CShTPSEnemy.h"

CShTPSEnemy::CShTPSEnemy(void)
: m_Position(0.0f,0.0f)
, m_Direction(0.0f,1.0f)
, m_Speed(0.0f)
, m_pSprite(shNULL)
, m_pCharacterController(shNULL)
, m_pGun(shNULL)
{
}
CShTPSEnemy::~CShTPSEnemy(void)
{
}

void CShTPSEnemy::Initialize(const CShIdentifier & levelIdentifier, CShTPSGun * defaultGun,ShEntity2 * sprite)
{
	m_pSprite = sprite;
	SH_ASSERT(shNULL != m_pSprite);
	//set the position of the TPSPlayer to the position of the sprite
	m_Position = ShObject::GetPosition2(m_pSprite);
	// Initialize the character controller with the level, the identifier, the position, the radius, the direction, the speed.
	ShCharacterController *	pCharacterController = shNULL;
	pCharacterController = ShCharacterController::Create(levelIdentifier, CShIdentifier("character_controller_character_001"), m_Position, 25.0, m_Direction, m_Speed);
	m_pCharacterController = pCharacterController;
	SH_ASSERT(shNULL != m_pCharacterController);

	m_pGun = defaultGun;
	m_pGun->Initialize(levelIdentifier);
}

void CShTPSEnemy::Update(void)
{
	//m_Position += m_Direction*m_Speed;
	ShCharacterController::SetWalkSpeed(m_pCharacterController, m_Speed);
	ShCharacterController::SetWalkDirection(m_pCharacterController, m_Direction);
	// Update the character controller to change the position
	ShCharacterController::Update(m_pCharacterController);
	// Change the position of the character according to the position of the character controller
	m_Position = ShCharacterController::GetPosition(m_pCharacterController);
	ShEntity2::SetPositionX(m_pSprite,m_Position.m_x);
	ShEntity2::SetPositionY(m_pSprite,m_Position.m_y);
}

CShTPSAmmo * CShTPSEnemy::Shoot(void)
{
	//+ShEntity2::GetHeight(m_pSprite)
	return m_pGun->Shoot(m_Position, m_Direction); // TODO position given is position+length of the sprite for shooting from the gun of the sprite
}

bool CShTPSEnemy::GunIsEmpty(void)
{
	return m_pGun->ClipIsEmpty();
}

void CShTPSEnemy::Reload(CShTPSAmmo * ammo)
{
	m_pGun->Reload(ammo);
}

void CShTPSEnemy::SetPosition(CShVector2 position)
{
	m_Position = position;
}

CShVector2 CShTPSEnemy::GetPosition(void)
{
	return m_Position;
}

void CShTPSEnemy::SetDirection(CShVector2 direction)
{
	m_Direction = direction;
}

CShVector2 CShTPSEnemy::GetDirection(void)
{
	return m_Direction;
}

void CShTPSEnemy::SetSpeed(float speed){
	m_Speed = speed;
}

float CShTPSEnemy::GetSpeed(void){
	return m_Speed;
}

void CShTPSEnemy::SetSprite(ShEntity2 * sprite)
{
	m_pSprite = sprite;
}

ShEntity2 * CShTPSEnemy::GetSprite (void)
{
	return m_pSprite;
}

void CShTPSEnemy::SetCharacterController(ShCharacterController * charactercontroller)
{
	m_pCharacterController = charactercontroller;
}

ShCharacterController *	CShTPSEnemy::GetCharacterController(void)
{
	return m_pCharacterController;
}

void CShTPSEnemy::SetGun(CShTPSGun * gun)
{
	m_pGun = gun;
}
CShTPSGun *	CShTPSEnemy::GetGun(void)
{
	return m_pGun;
}