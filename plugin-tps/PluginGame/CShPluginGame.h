#ifndef __CSHPLUGINTRANSLATE_H
#define __CSHPLUGINTRANSLATE_H

#include <ShSDK/ShSDK.h>
#include <ShEngineExt/ShEngineExt.h>

class CShPluginGame : public CShPlugin
{

public:
	

	// Constructor / Destructor
								CShPluginGame				(void);
	virtual						~CShPluginGame				(void);

	bool						Initialize					(const CShIdentifier & identifier);
	bool						Release						(void);

	virtual	void				OnPlayStart					(void);
	virtual	void				OnPlayStop					(void);
	virtual	void				OnPlayPause					(void);
	virtual	void				OnPlayResume				(void);

	virtual	void				OnPreUpdate					(void);
	virtual	void				OnPostUpdate				(float dt);

	DECLARE_VARIABLES();

private:

	CShIdentifier m_levelIdentifier;

	ShEntity2 * m_pBackground;
	ShEntity2 * m_pPlayer;

	float m_fScale;
};

#endif // __CSHPLUGINROTATE_H