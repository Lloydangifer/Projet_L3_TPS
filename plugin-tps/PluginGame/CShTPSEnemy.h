#ifndef __CSHTPSENEMY_H
#define __CSHTPSENEMY_H

#include <ShSDK/ShSDK.h>
#include <ShEngineExt/ShEngineExt.h>

#include "CShTPSCharacter.h"


class CShTPSEnemy: public CShTPSCharacter
{
public:
	void			Initialize			(const CShIdentifier & levelIdentifier, CShTPSGun * defaultGun, ShEntity2 *	sprite, CShString enemyCharacterControlleridentifier);
};

#endif // __CSHTPSENEMY_H