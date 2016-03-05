#ifndef __CSHTPSCAMERA_H
#define __CSHTPSCAMERA_H

#include <ShSDK/ShSDK.h>
#define MAX_CAMERAS 3


class CShTPSCamera
{
	public:
				// Constructor / Destructor
									CShTPSCamera				(void);
		virtual						~CShTPSCamera				(void);

		void						Initialize					(void);
		void						Update						(CShVector2 playerPos, CShVector2 playerDir);

		void						DoStuff1					(void);
		void						DoStuff2					(void);

		void						SwitchCameraStyle			(void);

	private:
		ShCamera *						m_pCamera;
		int							m_pCameraStyle;
};
#endif // __CSHTPSCAMERA_H