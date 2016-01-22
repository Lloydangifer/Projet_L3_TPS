#include "CShTPSGun.h"

#define DEFAULT_AMMO_NUMBER  6

CShTPSGun::CShTPSGun(float power, CShString name)
: m_Power(power)
, m_Name(name)
{
	for(int i=0; i<DEFAULT_AMMO_NUMBER; i++)
	{
		CShTPSAmmo * ammo = new CShTPSAmmo(m_Power);
		m_Clip.Add(ammo);
	}
}
CShTPSGun::~CShTPSGun(void)
{
}

void CShTPSGun::Update(void)
{
	// ??
}

void CShTPSGun::Shoot(CShVector2 position, CShVector2 direction)
{
	// TODO
}

void CShTPSGun::SetPower(float power)
{
	m_Power = power;
}

float CShTPSGun::GetPower(void)
{
	return m_Power;
}

void CShTPSGun::SetName(CShString name)
{
	m_Name = name;
}

CShString CShTPSGun::GetName(void)
{
	return m_Name;
}