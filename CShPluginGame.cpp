#include "CShPluginGame.h"

BEGIN_DERIVED_CLASS(CShPluginGame, CShPlugin)
	// ...
END_CLASS()


// Inputs to move and turn
ShInput *					g_pInputUp				= shNULL;
ShInput *					g_pInputLeft			= shNULL;
ShInput *					g_pInputRight			= shNULL;
ShInput *					g_pInputShoot			= shNULL;




/**
 * Constructor
 */
CShPluginGame::CShPluginGame(void)
: CShPlugin(CShIdentifier("TPS"))
, m_levelIdentifier(GID(NULL))
, m_pBackground(shNULL)
, m_pTpsPlayer(new CShTPSPlayer())
{

}

/**
 * Destructor
 */
CShPluginGame::~CShPluginGame(void)
{

}

/**
 * Initialize
 */
bool CShPluginGame::Initialize(const CShIdentifier & identifier)
{
	m_levelIdentifier = identifier;

	return(true);
}

/**
 * Release
 */
bool CShPluginGame::Release(void)
{
	m_levelIdentifier = GID(NULL);

	return(true);
}
	
/**
 * Called when the plugin is started
 */
void CShPluginGame::OnPlayStart(const CShIdentifier & levelIdentifier)
{
	m_pBackground = ShEntity2::Find(m_levelIdentifier, CShIdentifier("sprite_tps_background"));
	SH_ASSERT(shNULL != m_pBackground);

	CShTPSGun * pDefaultGun = new CShTPSGun(5.0f, CShString("Desert Eagle"));

	m_pTpsPlayer->Initialize(m_levelIdentifier, pDefaultGun);

	//create inputs
	g_pInputUp = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_up, 0.5f);
	g_pInputRight = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_right, 0.5f);
	g_pInputLeft = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_left, 0.5f);
	g_pInputShoot = ShInput::CreateInputJustPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_space, 0.5f);

	ShCollisionShape::GetCollisionShapeArray(levelIdentifier,m_aCollisionShape);
}

/**
 * Called when the plugin is stopped
 */
void CShPluginGame::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	// nothing here
}

/**
 * Called when the plugin is paused
 */
void CShPluginGame::OnPlayPause(const CShIdentifier & levelIdentifier)
{
	// nothing here
}

/**
 * Called when the plugin is resumed
 */
void CShPluginGame::OnPlayResume(const CShIdentifier & levelIdentifier)
{
	// nothing here
}

/**
 * Called before the engine updates itself
 */
void CShPluginGame::OnPreUpdate(void)
{
	// nothing here
}

/**
 * Called after the engine updates itself
 */
void CShPluginGame::OnPostUpdate(float dt)
{
	// Change the walk speed/direction
	if (ShInput::GetValue(g_pInputUp) > 0.2f)
	{
		m_pTpsPlayer->SetSpeed(100.0f);
	}
	else
	{
		m_pTpsPlayer->SetSpeed(0.0f);
	}

	if (ShInput::GetValue(g_pInputLeft) > 0.2f)
	{
		CShVector2 direction = m_pTpsPlayer->GetDirection();
		direction.Rotate(0.05f);
		m_pTpsPlayer->SetDirection(direction);
		ShEntity2::Rotate(m_pTpsPlayer->GetSprite(),CShEulerAngles(0, 0, 0.05f));
	}
	
	if (ShInput::GetValue(g_pInputRight) > 0.2f)
	{
		CShVector2 direction = m_pTpsPlayer->GetDirection();
		direction.Rotate(-0.05f);
		m_pTpsPlayer->SetDirection(direction);
		ShEntity2::Rotate(m_pTpsPlayer->GetSprite(),CShEulerAngles(0, 0, -0.05f));
	}

	if (ShInput::GetValue(g_pInputShoot) > 0.2f)
	{
		if(!m_pTpsPlayer->GunIsEmpty())
		{
			m_aBullets.Add(m_pTpsPlayer->Shoot());
		}
	}
	for(int a=0; a<m_aBullets.GetCount(); a++) // pour chaque balle
	{
		CShVector2 position = m_aBullets.At(a)->GetPosition()+ m_aBullets.At(a)->GetDirection()*m_aBullets.At(a)->GetSpeed();
		CShSegment2 * trajectoire = new CShSegment2(m_aBullets.At(a)->GetPosition(),position);
		for(int i=0; i<m_aCollisionShape.GetCount(); i++) // pour chaque collision shape
		{
			int nbPoints = ShCollisionShape::GetPointCount(m_aCollisionShape.At(i)); // on récupère le nombre de point du collisionshape
			for(int j=0; j<nbPoints; j++) // pour chaque point on va établir un segment avec le point contiguë pour vérifier l'intersection avec la trajectoire de la balle
			{
				int k;
				if(j == nbPoints-1)
				{
					k=0;
				}
				else
				{
					k=j+1;
				}
				CShSegment2 * segment = new CShSegment2(ShCollisionShape::GetPoint(m_aCollisionShape.At(i),j), ShCollisionShape::GetPoint(m_aCollisionShape.At(i),k));
				if(shTRUE == shIntersect(*trajectoire, *segment))
				{
					m_aBullets.At(a)->SetMoving(false);
				}
			}
		}
	}
	for(int i=0; i<m_aBullets.GetCount(); i++)
	{
		if(false == m_aBullets.At(i)->GetMoving())
		{
			m_pTpsPlayer->Reload(m_aBullets.At(i));
			m_aBullets.Remove(i);
		}
	}
	m_pTpsPlayer->Update();
	m_aBullets.ElementsUpdate(dt);
}