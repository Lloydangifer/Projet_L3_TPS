#include "CShTPSPlayer.h"




CShTPSPlayer::CShTPSPlayer(void)
{
	m_Speed=0.0f;
	m_Direction.SetXY(0.0f,0.0f);
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