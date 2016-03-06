#include "CShTPSAmmo.h"
#include "CShTPSCharacter.h"

CShTPSAmmo::CShTPSAmmo(float speed)
: m_Position(0.0f,0.0f)
, m_Direction(0.0f,0.0f)
, m_Speed(speed)
, m_Moving(false)
, m_pSprite(shNULL)
, m_Origin(shNULL)
, m_3d(false)
{
}
CShTPSAmmo::~CShTPSAmmo(void)
{
}

void CShTPSAmmo::Initialize(const CShIdentifier & levelIdentifier, CShTPSCharacter * origin)
{
	m_Origin = origin;
	if( origin->Is3D() )
	{
		m_pModel = ShEntity3::CreateEntity3(levelIdentifier, CShIdentifier(), ShLayer::Find(GID(layer_default)), false, CShVector3(0.0f,0.0f,150.0f), CShEulerAngles(0.0f,0.0f,0.0f), CShVector3(1.0f,1.0f,1.0f), ShMesh::Find(CShIdentifier("arrow_standard")));
		SH_ASSERT(shNULL != m_pModel);
		m_3d = true;
	}
	else
	{
		m_pModel = shNULL;
	}

	m_pSprite = ShEntity2::Create(levelIdentifier, CShIdentifier(), GID(layer_default), CShIdentifier("tps"), CShIdentifier("bullet"), CShVector3(0.0f,0.0f,1.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));

	SH_ASSERT(shNULL != m_pSprite);
	ShObject::SetShow(m_pSprite,false);
	if (m_3d) ShObject::SetShow(m_pModel,false);
}

void CShTPSAmmo::Update(float dt)
{
	m_Position += m_Direction*m_Speed;
	ShEntity2::SetPositionX(m_pSprite,m_Position.m_x);
	ShEntity2::SetPositionY(m_pSprite,m_Position.m_y);
	if (m_3d)
	{
		ShEntity3::SetPositionX(m_pModel,m_Position.m_x);
		ShEntity3::SetPositionY(m_pModel,m_Position.m_y);
	}
}

void CShTPSAmmo::SetPosition(CShVector2 position)
{
	m_Position = position;
}

CShVector2 CShTPSAmmo::GetPosition(void)
{
	return m_Position;
}

void CShTPSAmmo::SetDirection(CShVector2 direction)
{
	m_Direction = direction;
}

CShVector2 CShTPSAmmo::GetDirection(void)
{
	return m_Direction;
}

void CShTPSAmmo::SetSpeed(float speed){
	m_Speed = speed;
}

float CShTPSAmmo::GetSpeed(void){
	return m_Speed;
}

void CShTPSAmmo::SetMoving(bool moving)
{
	m_Moving=moving;
}

bool CShTPSAmmo::isMoving(void)
{
	return m_Moving;
}

void CShTPSAmmo::SetSprite(ShEntity2 * sprite)
{
	m_pSprite = sprite;
}

ShEntity2 * CShTPSAmmo::GetSprite(void)
{
	return m_pSprite;
}

void CShTPSAmmo::SetModel(ShEntity3 * model)
{
	m_pModel = model;
}
ShEntity3 * CShTPSAmmo::GetModel(void)
{
	return m_pModel;
}


void CShTPSAmmo::SetOrigin(CShTPSCharacter * origin)
{
	m_Origin = origin;
}

CShTPSCharacter * CShTPSAmmo::GetOrigin(void)
{
	return m_Origin;
}

bool CShTPSAmmo::Is3D(void)
{
	return m_3d;
}