#ifndef __CSHTPSPLAYER_H
#define __CSHTPSPLAYER_H

#include <ShSDK/ShSDK.h>
#include <ShEngineExt/ShEngineExt.h>

#include "CShTPSCharacter.h"
#include "CShTPSGlobal.h"


class CShTPSPlayer: public CShTPSCharacter
{
public:
	void						Initialize					(const CShIdentifier & levelIdentifier, CShTPSGun * defaultGun);
	void						SwitchToAnimationRun		(void);
	void						SwitchToAnimationIdle		(void);
	void						SwitchToAnimationAttack		(void);
};

#endif // __CSHTPSPLAYER_H