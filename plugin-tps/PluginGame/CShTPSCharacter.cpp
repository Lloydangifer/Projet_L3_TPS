#include "CShTPSCharacter.h"

CShTPSCharacter::CShTPSCharacter(void)
: m_Position(0.0f,0.0f)
, m_Direction(0.0f,1.0f)
, m_Speed(0.0f)
, m_pSprite(shNULL)
, m_pModel(shNULL)
, m_pAnimIdle(shNULL)
, m_pAnimRun(shNULL)
, m_pCharacterController(shNULL)
, m_pGun(shNULL)
, m_Alive(true)
, m_3d(false)
{
}
CShTPSCharacter::~CShTPSCharacter(void)
{
	delete m_pGun;
}

void CShTPSCharacter::Initialize(const CShIdentifier & levelIdentifier, CShTPSGun * defaultGun)
{
	//set the position of the Character to the position of the sprite or the model if 3d
	if (m_3d)
	{
		m_Position = ShObject::GetPosition2(m_pModel);
		ShObject::SetPosition(m_pSprite, m_Position.m_x, m_Position.m_y, 1.0f);
		/*float rotation = ShObject::GetRotation(m_pModel).GetZ();
		m_Direction = CShVector2(std::acos(rotation),std::asin(rotation));*/
	}
	else
	{
		m_Position = ShObject::GetPosition2(m_pSprite);
		/*float rotation = ShObject::GetRotation(m_pSprite).GetZ();
		m_Direction = CShVector2(std::asin(rotation),std::acos(rotation));*/
	}

	
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

	if (m_3d)
	{
		ShObject::SetPositionX(m_pModel,m_Position.m_x);
		ShObject::SetPositionY(m_pModel,m_Position.m_y);
	}
}

CShTPSAmmo * CShTPSCharacter::Shoot(void)
{
	m_pGun->SetCoolDown(0.0f);
	CShEulerAngles rotation;
	if(m_3d)
	{
		rotation = ShObject::GetRotation(m_pModel);
	}
	else
	{
		rotation = ShObject::GetRotation(m_pSprite);
	}
	
	CShVector2 position(m_Position.m_x + (m_Direction.m_x * (ShEntity2::GetHeight(m_pSprite)/2)), m_Position.m_y + (m_Direction.m_y * (ShEntity2::GetHeight(m_pSprite)/2)));
 
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
	if (m_3d)
	{
		ShObject::SetShow(m_pModel, false);
	}
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

void CShTPSCharacter::SetSprite(ShEntity2 * sprite)
{
	m_pSprite = sprite;
}

ShEntity2 * CShTPSCharacter::GetSprite (void)
{
	return m_pSprite;
}

void CShTPSCharacter::SetModel(ShEntity3 * model)
{
	m_pModel = model;
}

ShEntity3 * CShTPSCharacter::GetModel (void)
{
	return m_pModel;
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

bool CShTPSCharacter::Is3D(void)
{
	return m_3d;
}