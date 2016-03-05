#include "CShTPSCharacter.h"

CShTPSCharacter::CShTPSCharacter(void)
: m_Position(0.0f,0.0f)
, m_Direction(0.0f,1.0f)
, m_Speed(0.0f)
, m_pSprite(shNULL)
, m_pAnimIdle(shNULL)
, m_pAnimRun(shNULL)
, m_pCharacterController(shNULL)
, m_pGun(shNULL)
, m_Alive(true)
{
}
CShTPSCharacter::~CShTPSCharacter(void)
{
	delete m_pGun;
}

void CShTPSCharacter::Initialize(const CShIdentifier & levelIdentifier, CShTPSGun * defaultGun)
{
	//set the position of the Character to the position of the sprite
	m_Position = ShObject::GetPosition2(m_pSprite);
	m_Direction = CShVector2(0.0f,1.0f);
	m_pGun = defaultGun;
	m_pGun->Initialize(levelIdentifier, this);
}

void CShTPSCharacter::Update(float dt)
{
	if(m_pGun->GetCoolDown() < m_pGun->GetFireRate())
	{
		m_pGun->AddToCoolDown(dt);
	}

	ShCharacterController::SetWalkSpeed(m_pCharacterController, m_Speed);
	ShCharacterController::SetWalkDirection(m_pCharacterController, m_Direction);
	// Update the character controller to change the position
	ShCharacterController::Update(m_pCharacterController);
	// Change the position of the sprite according to the position of the character controller
	m_Position = ShCharacterController::GetPosition(m_pCharacterController);
	ShObject::SetPositionX(m_pSprite,m_Position.m_x);
	ShObject::SetPositionY(m_pSprite,m_Position.m_y);
}

CShTPSAmmo * CShTPSCharacter::Shoot(void)
{
	m_pGun->SetCoolDown(0.0f);
	CShEulerAngles rotation = ShObject::GetRotation(m_pSprite);
	CShVector2 position = m_Position;
	if(ShObject::e_type_entity2 == ShObject::GetType(m_pSprite))
	{
		CShVector2 position(m_Position.m_x + (m_Direction.m_x * (ShEntity2::GetHeight((ShEntity2 *)m_pSprite)/2)), m_Position.m_y + (m_Direction.m_y * (ShEntity2::GetHeight((ShEntity2 *)m_pSprite)/2)));
	}
	return m_pGun->Shoot(position, m_Direction, rotation);
}

bool CShTPSCharacter::GunIsEmpty(void)
{
	return m_pGun->ClipIsEmpty();
}

void CShTPSCharacter::Reload(CShTPSAmmo * ammo)
{
	m_pGun->Reload(ammo);
}

bool CShTPSCharacter::isAlive(void)
{
	return m_Alive;
}

void CShTPSCharacter::death(void)
{
	m_Alive = false;
	ShObject::SetShow(m_pSprite, false);
	ShCharacterController::Disable(m_pCharacterController);
}

bool CShTPSCharacter::ReadyToShoot(void)
{
	return (m_pGun->GetCoolDown() >= m_pGun->GetFireRate() && m_Alive);
}

void CShTPSCharacter::SetPosition(CShVector2 position)
{
	m_Position = position;
}

CShVector2 CShTPSCharacter::GetPosition(void)
{
	return m_Position;
}

void CShTPSCharacter::SetDirection(CShVector2 direction)
{
	m_Direction = direction;
}

CShVector2 CShTPSCharacter::GetDirection(void)
{
	return m_Direction;
}

void CShTPSCharacter::SetSpeed(float speed)
{
	m_Speed = speed;
}

float CShTPSCharacter::GetSpeed(void)
{
	return m_Speed;
}

void CShTPSCharacter::SetSprite(ShObject * sprite)
{
	m_pSprite = sprite;
}

ShObject * CShTPSCharacter::GetSprite (void)
{
	return m_pSprite;
}

void CShTPSCharacter::SetCharacterController(ShCharacterController * charactercontroller)
{
	m_pCharacterController = charactercontroller;
}

ShCharacterController *	CShTPSCharacter::GetCharacterController(void)
{
	return m_pCharacterController;
}

void CShTPSCharacter::SetGun(CShTPSGun * gun)
{
	m_pGun = gun;
}
CShTPSGun *	CShTPSCharacter::GetGun(void)
{
	return m_pGun;
}