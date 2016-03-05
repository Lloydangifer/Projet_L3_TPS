#ifndef __CSHTPSCHARACTER_H
#define __CSHTPSCHARACTER_H

#include <ShSDK/ShSDK.h>
#include <ShEngineExt/ShEngineExt.h>

#include "CShTPSGun.h"


class CShTPSCharacter
{
public:
		// Constructor / Destructor
								CShTPSCharacter				(void);
	virtual						~CShTPSCharacter			(void);

	void						Initialize					(const CShIdentifier & levelIdentifier, CShTPSGun * defaultGun);
	void						Update						(float dt);
	CShTPSAmmo		*			Shoot						(void);
	bool						GunIsEmpty					(void);
	void						Reload						(CShTPSAmmo * ammo);
	bool						isAlive						(void);
	void						death						(void);
	bool						ReadyToShoot				(void);

		// Setters & Getters
	void						SetPosition					(CShVector2 position);
	CShVector2					GetPosition					(void);

	void						SetDirection				(CShVector2 direction);
	CShVector2					GetDirection				(void);

	void						SetSpeed					(float speed);
	float						GetSpeed					(void);

	void						SetSprite					(ShObject * sprite);
	ShObject *					GetSprite					(void);

	void						SetCharacterController		(ShCharacterController * charactercontroller);
	ShCharacterController *		GetCharacterController		(void);

	void						SetGun						(CShTPSGun * gun);
	CShTPSGun *					GetGun						(void);

	bool						Is3D						(void);

protected:
	CShVector2					m_Position;
	CShVector2					m_Direction;	
	float						m_Speed;
	ShObject *					m_pSprite;
	ShAnimation *				m_pAnimIdle;
	ShAnimation *				m_pAnimRun;
	ShAnimation *				m_pAnimAttack;
	ShCharacterController *		m_pCharacterController;
	CShTPSGun *					m_pGun;
	bool						m_Alive;
	bool						m_3d;
};

#endif // __CSHTPSCHARACTER_H