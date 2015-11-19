#ifndef __CSHTPSPLAYER_H
#define __CSHTPSPLAYER_H

#include <ShSDK/ShSDK.h>

class CShTPSPlayer
{
public:
		// Constructor / Destructor
								CShTPSPlayer				(void);
	virtual						~CShTPSPlayer				(void);

private:
	CShVector2 m_Position;
};

#endif // __CSHTPSPLAYER_H