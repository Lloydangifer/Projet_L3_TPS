#ifndef __CSHTPSENEMY_H
#define __CSHTPSENEMY_H

#include <ShSDK/ShSDK.h>
#include <ShEngineExt/ShEngineExt.h>

#include "CShTPSGun.h"


class CShTPSEnemy
{
public:
		// Constructor / Destructor
								CShTPSEnemy				(void);
	virtual						~CShTPSEnemy				(void);

	void						Initialize					(const CShIdentifier & levelIdentifier, CShTPSGun * defaultGun, ShEntity2 *	sprite);
	void						Update						(void);
	CShTPSAmmo		*			Shoot						(void);
	bool						GunIsEmpty					(void);
	void						Reload						(CShTPSAmmo * ammo);

		// Setters & Getters
	void						SetPosition					(CShVector2 position);
	CShVector2					GetPosition					(void);

	void						SetDirection				(CShVector2 direction);
	CShVector2					GetDirection				(void);

	void						SetSpeed					(float speed);
	float						GetSpeed					(void);

	void						SetSprite					(ShEntity2 * sprite);
	ShEntity2 *					GetSprite					(void);

	void						SetCharacterController		(ShCharacterController * charactercontroller);
	ShCharacterController *		GetCharacterController		(void);

	void						SetGun						(CShTPSGun * gun);
	CShTPSGun *					GetGun						(void);

private:
	CShVector2					m_Position;
	CShVector2					m_Direction;	
	float						m_Speed;
	ShEntity2 *					m_pSprite;
	ShCharacterController *		m_pCharacterController;
	CShTPSGun *					m_pGun;
};

#endif // __CSHTPSENEMY_H