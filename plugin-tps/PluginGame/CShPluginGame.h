#ifndef __CSHPLUGINGAME_H
#define __CSHPLUGINGAME_H

#include <ShSDK/ShSDK.h>
#include <ShEngineExt/ShEngineExt.h>

#include "CShTPSGlobal.h"
#include "CShTPSPlayer.h"
#include "CShTPSEnemy.h"
#include "CShTPSCollisionsManager.h"
#include "CShTPSCamera.h"

class CShPluginGame : public CShPlugin
{

public:
	

	// Constructor / Destructor
								CShPluginGame				(void);
	virtual						~CShPluginGame				(void);

	bool						Initialize					(const CShIdentifier & identifier);
	bool						Release						(void);

	virtual	void				OnPlayStart					(const CShIdentifier & levelIdentifier);
	virtual	void				OnPlayStop					(const CShIdentifier & levelIdentifier);
	virtual	void				OnPlayPause					(const CShIdentifier & levelIdentifier);
	virtual	void				OnPlayResume				(const CShIdentifier & levelIdentifier);

	virtual	void				OnPreUpdate					(void);
	virtual	void				OnPostUpdate				(float dt);

	DECLARE_VARIABLES();

private:

	CShIdentifier					m_levelIdentifier;
	CShArray<ShObject *>			m_aBackground;
	CShTPSPlayer *					m_pTpsPlayer;
	CShArray<CShTPSAmmo *>			m_aBullets;
	CShArray<CShTPSEnemy *>			m_aEnemies;
	CShTPSCollisionsManager	*		m_pCollisionsManager;
	CShTPSCamera *					m_pTpsCamera;

	void						Win							(void);
	void						Lose							(void);
};

#endif // __CSHPLUGINGAME_H