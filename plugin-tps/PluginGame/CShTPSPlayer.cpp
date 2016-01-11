#include "CShTPSPlayer.h"

CShTPSPlayer::CShTPSPlayer(void)
{
	m_Speed=0.0f;
	m_Direction.SetXY(0.0f,1.0f);
	m_pSprite= shNULL;
}
CShTPSPlayer::~CShTPSPlayer(void)
{
}

void CShTPSPlayer::Update(void)
{
	m_Position += m_Direction*m_Speed;
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