#ifndef __CSHTPSENEMY_H
#define __CSHTPSENEMY_H

#include <ShSDK/ShSDK.h>
#include <ShEngineExt/ShEngineExt.h>

#include "CShTPSCharacter.h"
#include "CShTPSGlobal.h"

enum EState
{
	e_state_idle,
	e_state_attack
};

class CShTPSEnemy: public CShTPSCharacter
{
public:
					CShTPSEnemy			(void);
	void			Initialize			(const CShIdentifier & levelIdentifier, const CShIdentifier & characterIdentifier, CShTPSGun * defaultGun, ShEntity2 *	sprite, CShString enemyCharacterControlleridentifier, ShEntity3 * model);
	void			Update				(float dt);

	// Setters & Getters
	void			SetTarget			(CShVector2 target);
	CShVector2		GetTarget			(void);

	EState			GetCurrentState		(void);

	void			Spawn				(void);

private:
	EState			m_CurrentState;
	CShVector2		m_Target;

	bool			HasReachedTarget	(void);
};

#endif // __CSHTPSENEMY_H