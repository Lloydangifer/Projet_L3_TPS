#ifndef __CSHTPSAMMO_H
#define __CSHTPSAMMO_H

#include <ShSDK/ShSDK.h>

class CShTPSCharacter;

class CShTPSAmmo
{
public:
		// Constructor / Destructor
								CShTPSAmmo					(float speed);
	virtual						~CShTPSAmmo					(void);


	void						Initialize					(const CShIdentifier & levelIdentifier, CShTPSCharacter * origin);
	void						Update						(float dt);

		// Setters & Getters
	void						SetPosition					(CShVector2 position);
	CShVector2					GetPosition					(void);

	void						SetDirection				(CShVector2 direction);
	CShVector2					GetDirection				(void);

	void						SetSpeed					(float speed);
	float						GetSpeed					(void);

	void						SetMoving					(bool moving);
	bool						isMoving					(void);

	void						SetSprite					(ShEntity2 * sprite);
	ShEntity2 *					GetSprite					(void);

	void						SetModel					(ShEntity3 * model);
	ShEntity3 *					GetModel					(void);

	void						SetOrigin					(CShTPSCharacter * origin);
	CShTPSCharacter *			GetOrigin					(void);

	bool						Is3D						(void);

private:
	CShVector2					m_Position;
	CShVector2					m_Direction;	
	float						m_Speed;
	bool						m_Moving;
	ShEntity2 *					m_pSprite;
	ShEntity3 *					m_pModel;
	CShTPSCharacter *			m_Origin;
	bool						m_3d;
};

#endif // __CSHTPSAMMO_H