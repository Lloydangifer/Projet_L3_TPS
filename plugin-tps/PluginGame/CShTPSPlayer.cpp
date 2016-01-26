#include "CShTPSPlayer.h"

CShTPSPlayer::CShTPSPlayer(void)
: m_Position(0.0f,0.0f)
, m_Direction(0.0f,1.0f)
, m_Speed(0.0f)
, m_pSprite(shNULL)
, m_pCharacterController(shNULL)
, m_pGun(shNULL)
{
}
CShTPSPlayer::~CShTPSPlayer(void)
{
}

void CShTPSPlayer::Initialize(const CShIdentifier & levelIdentifier, CShTPSGun * defaultGun)
{
	m_pSprite = ShEntity2::Find(levelIdentifier, CShIdentifier("sprite_tps_player"));
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

void CShTPSPlayer::Update(void)
{
	//m_Position += m_Direction*m_Speed;
	ShCharacterController::SetWalkSpeed(m_pCharacterController, m_Speed);
	ShCharacterController::SetWalkDirection(m_pCharacterController, m_Direction);
	// Update the character controller to change the position
	ShCharacterController::Update(m_pCharacterController);
	// Change the position of the character according to the position of the character controller
	m_Position = ShCharacterController::GetPosition(m_pCharacterController);
}

void CShTPSPlayer::Render(void)
{
	ShEntity2::SetPositionX(m_pSprite,m_Position.m_x);
	ShEntity2::SetPositionY(m_pSprite,m_Position.m_y);
}

CShTPSAmmo * CShTPSPlayer::Shoot(void)
{
	return m_pGun->Shoot(m_Position, m_Direction); // TODO position given is position+length of the sprite for shooting from the gun of the sprite
}

bool CShTPSPlayer::GunIsEmpty(void)
{
	return m_pGun->ClipIsEmpty();
}

void CShTPSPlayer::SetPosition(CShVector2 position)
{
	m_Position = position;
}

CShVector2 CShTPSPlayer::GetPosition(void)
{
	return m_Position;
}

void CShTPSPlayer::SetDirection(CShVector2 direction)
{
	m_Direction = direction;
}

CShVector2 CShTPSPlayer::GetDirection(void)
{
	return m_Direction;
}

void CShTPSPlayer::SetSpeed(float speed){
	m_Speed = speed;
}

float CShTPSPlayer::GetSpeed(void){
	return m_Speed;
}

void CShTPSPlayer::SetSprite(ShEntity2 * sprite)
{
	m_pSprite = sprite;
}

ShEntity2 * CShTPSPlayer::GetSprite (void)
{
	return m_pSprite;
}

void CShTPSPlayer::SetCharacterController(ShCharacterController * charactercontroller)
{
	m_pCharacterController = charactercontroller;
}

ShCharacterController *	CShTPSPlayer::GetCharacterController(void)
{
	return m_pCharacterController;
}

void CShTPSPlayer::SetGun(CShTPSGun * gun)
{
	m_pGun = gun;
}
CShTPSGun *	CShTPSPlayer::GetGun(void)
{
	return m_pGun;
}