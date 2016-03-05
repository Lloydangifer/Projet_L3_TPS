#ifndef __CSHTPSCAMERA_H
#define __CSHTPSCAMERA_H

#include <ShSDK/ShSDK.h>

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


	private:
		ShCamera *						m_pCamera;
};
#endif // __CSHTPSCAMERA_H