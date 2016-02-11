#include "CShTPSGun.h"

#define DEFAULT_AMMO_NUMBER  6

CShTPSGun::CShTPSGun(float power, CShString name)
: m_Power(power)
, m_Name(name)
, m_aClip()
{
}

CShTPSGun::~CShTPSGun(void)
{
}

void CShTPSGun::Initialize(const CShIdentifier & levelIdentifier)
{
	for(int i=0; i<DEFAULT_AMMO_NUMBER; i++)
	{
		CShTPSAmmo * ammo = new CShTPSAmmo(m_Power);
		ammo->Initialize(levelIdentifier);
		m_aClip.Add(ammo);
	}
	SH_ASSERT(true != m_aClip.IsEmpty());
}

void CShTPSGun::Update(void)
{
	// ??
}

CShTPSAmmo * CShTPSGun::Shoot(CShVector2 position, CShVector2 direction)
{
		CShTPSAmmo * ammo = new CShTPSAmmo(m_Power);
		ammo = m_aClip.Back();
		m_aClip.RemoveBack();
		ammo->SetPosition(position);
		ammo->SetDirection(direction);
		ammo->SetMoving(true);
		ShObject::SetShow(ammo->GetSprite(),true);
		return ammo;
}

bool CShTPSGun::ClipIsEmpty(void)
{
	return m_aClip.IsEmpty();
}

void CShTPSGun::Reload(CShTPSAmmo * ammo)
{
	ShObject::SetShow(ammo->GetSprite(),false);
	ammo->SetPosition(CShVector2(0.0f,0.0f));
	ammo->SetDirection(CShVector2(0.0f,0.0f));
	m_aClip.Add(ammo);
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

void CShTPSGun::SetClip(CShArray<CShTPSAmmo *>	clip)
{
	m_aClip = clip;
}

CShArray<CShTPSAmmo *> CShTPSGun::GetClip(void)
{
	return m_aClip;
}