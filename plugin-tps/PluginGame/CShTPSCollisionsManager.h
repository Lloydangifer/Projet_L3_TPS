#ifndef __CSHTPSCOLLISIONSMANAGER_H
#define __CSHTPSCOLLISIONSMANAGER_H

#include <ShSDK/ShSDK.h>
#include <ShEngineExt/ShEngineExt.h>

#include "CShTPSCharacter.h"

class CShTPSCollisionsManager
{
public:
		// Constructor / Destructor
								CShTPSCollisionsManager					(void);
	virtual						~CShTPSCollisionsManager				(void);

	void						Update									(void);
	void						Initialize								(const CShIdentifier & levelIdentifier);
	void						CheckBulletCollisionShapeCollision		(CShTPSAmmo* bullet);
	void						CheckBulletCharacterCollision			(CShTPSAmmo* bullet, CShTPSCharacter* character);

private:
		CShArray<ShCollisionShape *>	m_aCollisionShape;
		int								m_CollisionShapeCount;
};

#endif // __CSHTPSCOLLISIONSMANAGER_H