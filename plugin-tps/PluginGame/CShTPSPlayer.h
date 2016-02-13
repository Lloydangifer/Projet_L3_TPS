#ifndef __CSHTPSPLAYER_H
#define __CSHTPSPLAYER_H

#include <ShSDK/ShSDK.h>
#include <ShEngineExt/ShEngineExt.h>

#include "CShTPSCharacter.h"


class CShTPSPlayer: public CShTPSCharacter
{
public:
	void						Initialize					(const CShIdentifier & levelIdentifier, CShTPSGun * defaultGun);

};

#endif // __CSHTPSPLAYER_H