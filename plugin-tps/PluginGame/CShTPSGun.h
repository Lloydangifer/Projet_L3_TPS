#ifndef __CSHTPSGUN_H
#define __CSHTPSGUN_H

#include <ShSDK/ShSDK.h>

#include "CShTPSAmmo.h"


class CShTPSGun
{
public:
		// Constructor / Destructor
								CShTPSGun					(float power, CShString name);
	virtual						~CShTPSGun					(void);


	void						Update						(void);
	void						Shoot						(CShVector2 position, CShVector2 direction);


		// Setters & Getters
	void						SetPower					(float power);
	float						GetPower					(void);

	void						SetName						(CShString name);
	CShString					GetName						(void);

private:
	float						m_Power;	//Value given by the gun as speed to its ammo
	CShString					m_Name;
	CShArray<CShTPSAmmo*>		m_Clip;
};

#endif // __CSHTPSGUN_H