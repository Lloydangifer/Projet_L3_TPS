#ifndef __CSHTPSPLAYER_H
#define __CSHTPSPLAYER_H

#include <ShSDK/ShSDK.h>


class CShTPSPlayer
{
public:
		// Constructor / Destructor
								CShTPSPlayer				(void);
	virtual						~CShTPSPlayer				(void);


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

	void						SetCharacterController		(ShCharacterController * charactercontroller);
	ShCharacterController *		GetCharacterController		(void);

private:
	CShVector2					m_Position;
	CShVector2					m_Direction;	
	float						m_Speed;
	ShEntity2 *					m_pSprite;
	ShCharacterController *		m_pCharacterController;
};

#endif // __CSHTPSPLAYER_H