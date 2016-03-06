#ifndef __CSHTPSGUN_H
#define __CSHTPSGUN_H

#include <ShSDK/ShSDK.h>

#include "CShTPSAmmo.h"


class CShTPSGun
{
public:
		// Constructor / Destructor
								CShTPSGun					(float power, CShString name, float firerate);
	virtual						~CShTPSGun					(void);

	void						Initialize					(const CShIdentifier & levelIdentifier, CShTPSCharacter * origin);
	CShTPSAmmo			*		Shoot						(CShVector2 position, CShVector2 direction, CShEulerAngles rotation);
	bool						ClipIsEmpty					(void);
	void						Reload						(CShTPSAmmo * ammo);
	void						AddToCoolDown				(float value);

		// Setters & Getters
	void						SetPower					(float power);
	float						GetPower					(void);

	void						SetName						(CShString name);
	CShString					GetName						(void);

	void						SetClip						(CShArray<CShTPSAmmo *>	clip);
	CShArray<CShTPSAmmo *>		GetClip						(void);

	void						SetCoolDown					(float cooldown);
	float						GetCoolDown					(void);

	void						SetFireRate					(float firerate);
	float						GetFireRate					(void);

private:
	float						m_Power;	//Value given by the gun as speed to its ammo
	CShString					m_Name;
	CShArray<CShTPSAmmo *>		m_aClip;
	float						m_FireRate;
	float						m_ShootCooldown;
};

#endif // __CSHTPSGUN_H