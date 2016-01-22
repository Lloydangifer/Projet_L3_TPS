#ifndef __CSHTPSAMMO_H
#define __CSHTPSAMMO_H

#include <ShSDK/ShSDK.h>


class CShTPSAmmo
{
public:
		// Constructor / Destructor
								CShTPSAmmo				(float speed);
	virtual						~CShTPSAmmo				(void);


	void						Update						(void);


		// Setters & Getters
	void						SetPosition					(CShVector2 position);
	CShVector2					GetPosition					(void);

	void						SetDirection				(CShVector2 direction);
	CShVector2					GetDirection				(void);

	void						SetSpeed					(float speed);
	float						GetSpeed					(void);

	void						SetSprite					(ShEntity2 * sprite);
	ShEntity2 *					GetSprite					(void);

private:
	CShVector2					m_Position;
	CShVector2					m_Direction;	
	float						m_Speed;
	bool						m_Moving;
	ShEntity2 *					m_pSprite;
};

#endif // __CSHTPSAMMO_H