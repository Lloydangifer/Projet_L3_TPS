#ifndef __CSHTPSCOLLISIONSMANAGER_H
#define __CSHTPSCOLLISIONSMANAGER_H

#include <ShSDK/ShSDK.h>
#include <ShEngineExt/ShEngineExt.h>

#include "CShTPSEnemy.h"
#include "CShTPSPlayer.h"

class CShTPSCollisionsManager
{
public:
		// Constructor / Destructor
								CShTPSCollisionsManager					(void);
	virtual						~CShTPSCollisionsManager				(void);

	void						Update									(void);
	void						Initialize								(const CShIdentifier & levelIdentifier);
	void						CheckBulletCollisionShapeCollision		(CShTPSAmmo* bullet);
	bool						CheckBulletCharacterCollision			(CShTPSAmmo* bullet, CShTPSCharacter* character);
	void						CheckPlayerEnemyViewField				(CShTPSPlayer* player, CShTPSEnemy* Enemy);

private:
		CShArray<ShCollisionShape *>	m_aCollisionShape;
		int								m_CollisionShapeCount;
};

#endif // __CSHTPSCOLLISIONSMANAGER_H