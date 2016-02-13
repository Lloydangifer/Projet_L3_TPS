#ifndef __CSHTPSENEMY_H
#define __CSHTPSENEMY_H

#include <ShSDK/ShSDK.h>
#include <ShEngineExt/ShEngineExt.h>

#include "CShTPSCharacter.h"

enum EState
{
	e_state_idle,
	e_state_attack
};

class CShTPSEnemy: public CShTPSCharacter
{
public:
					CShTPSEnemy			(void);
	void			Initialize			(const CShIdentifier & levelIdentifier, CShTPSGun * defaultGun, ShEntity2 *	sprite, CShString enemyCharacterControlleridentifier);
	void			Update				(void);

	// Setters & Getters
	void			SetTarget			(CShVector2 target);
	CShVector2		GetTarget			(void);

private:
	EState			m_CurrentState;
	CShVector2		m_Target;
};

#endif // __CSHTPSENEMY_H