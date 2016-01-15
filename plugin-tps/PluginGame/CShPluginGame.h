#ifndef __CSHPLUGINGAME_H
#define __CSHPLUGINGAME_H

#include <ShSDK/ShSDK.h>
#include <ShEngineExt/ShEngineExt.h>
#include "CShTPSPlayer.h"

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

	CShIdentifier m_levelIdentifier;

	ShEntity2 * m_pBackground;
	CShTPSPlayer * m_pTpsPlayer;
};

#endif // __CSHPLUGINGAME_H