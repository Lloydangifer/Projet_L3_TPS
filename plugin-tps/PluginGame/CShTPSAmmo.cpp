#include "CShTPSAmmo.h"

CShTPSAmmo::CShTPSAmmo(float speed)
: m_Position(0.0f,0.0f)
, m_Direction(0.0f,0.0f)
, m_Speed(speed)
, m_Moving(false)
, m_pSprite(shNULL)
{
}
CShTPSAmmo::~CShTPSAmmo(void)
{
}

void CShTPSAmmo::Update(void)
{
	m_Position += m_Direction*m_Speed;
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
void CShTPSAmmo::SetSprite(ShEntity2 * sprite)
{
	m_pSprite = sprite;
}
ShEntity2 * CShTPSAmmo::GetSprite (void)
{
	return m_pSprite;
}