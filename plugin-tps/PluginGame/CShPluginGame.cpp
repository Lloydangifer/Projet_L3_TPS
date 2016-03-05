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
, m_aBackground()
, m_pTpsPlayer(new CShTPSPlayer())
, m_pCollisionsManager(new CShTPSCollisionsManager())
, m_pCamera(shNULL)
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
	// Create camera
	/*m_pCamera = ShCamera::Create(GID(global), GID(camera_free), false);
	SH_ASSERT(NULL != m_pCamera);
	ShCamera::SetPosition(m_pCamera, CShVector3(-300.0f,-1500.0f, 1000.0f));
	ShCamera::SetTarget(m_pCamera, CShVector3(0.0f, 0.0f, 100.0f));
	ShCamera::SetFarPlaneDistance(m_pCamera, 3000.0f);

	ShCamera::SetCurrent2D(m_pCamera);
	ShCamera::SetCurrent3D(m_pCamera);*/

	bool floorLeft = true;
	int nbFloor = 0;
	while(floorLeft)
	{
		nbFloor++;
		CShString floorIdentifier(FLOOR_NAME);
		floorIdentifier += CShString::FromInt(nbFloor);
		ShObject * floor;
		floor = ShEntity2::Find(m_levelIdentifier, CShIdentifier(floorIdentifier));
		if(shNULL == floor)
		{
			floor = ShEntity3::Find(m_levelIdentifier, CShIdentifier(floorIdentifier));
		}
		if(shNULL == floor)
		{
			floorLeft = false;
			SH_TRACE("[PLUGIN TPS][ON PLAY START] No floor left\n");
		}
		else
		{
			m_aBackground.Add(floor);
			SH_TRACE("[PLUGIN TPS][ON PLAY START] Floor Added !\n");
		}
	}
	SH_ASSERT(!m_aBackground.IsEmpty());

	CShTPSGun * pDefaultGun = new CShTPSGun(DESERT_EAGLE_POWER, CShString(DESERT_EAGLE_NAME), DESERT_EAGLE_FIRERATE);

	m_pTpsPlayer->Initialize(m_levelIdentifier, pDefaultGun);

	m_pCollisionsManager->Initialize(m_levelIdentifier);

	//create inputs
	g_pInputUp = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_up, 0.5f);
	g_pInputRight = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_right, 0.5f);
	g_pInputLeft = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_left, 0.5f);
	g_pInputShoot = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_space, 0.5f);

	//create and initialize the ennemies
	bool searchEnemies = true;
	int nbEnemies = 0;
	while(searchEnemies)
	{
		nbEnemies++;
		CShString enemyIdentifier(ENEMY_SPRITE_NAME);
		CShString enemyCharacterControlleridentifier(ENEMY_CHARACTERCONTROLLER_NAME);
		enemyIdentifier += CShString::FromInt(nbEnemies);
		enemyCharacterControlleridentifier += CShString::FromInt(nbEnemies);
		ShObject * pEnemySprite;
		pEnemySprite = ShEntity2::Find(levelIdentifier, CShIdentifier(enemyIdentifier));
		if(shNULL == pEnemySprite) // if there is no 2D sprite, the game search for a 3D model
		{
			pEnemySprite = ShEntity3::Find(levelIdentifier, CShIdentifier(enemyIdentifier));
		}
		if(shNULL == pEnemySprite) // if there is no more enemies in the level we stop the research
		{
			searchEnemies = false;
		}
		else
		{
			CShTPSGun * pEnemyGun = new CShTPSGun(DESERT_EAGLE_POWER, CShString(DESERT_EAGLE_NAME), DESERT_EAGLE_FIRERATE);
			CShTPSEnemy * enemy = new CShTPSEnemy();
			enemy->Initialize(m_levelIdentifier, pEnemyGun, pEnemySprite, enemyCharacterControlleridentifier);
			m_aEnemies.Add(enemy);
		}
	}
	//ShCamera::SetPosition(m_pCamera, CShVector3(m_pTpsPlayer->GetPosition(), 100.0f));
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
		direction.Rotate(ROTATION_SPEED);
		m_pTpsPlayer->SetDirection(direction);
		ShEntity2::Rotate(m_pTpsPlayer->GetSprite(),CShEulerAngles(0, 0, ROTATION_SPEED));
	}
	
	if (ShInput::GetValue(g_pInputRight) > 0.2f)
	{
		CShVector2 direction = m_pTpsPlayer->GetDirection();
		direction.Rotate(-ROTATION_SPEED);
		m_pTpsPlayer->SetDirection(direction);
		ShEntity2::Rotate(m_pTpsPlayer->GetSprite(),CShEulerAngles(0, 0, -ROTATION_SPEED));
	}

	if (ShInput::GetValue(g_pInputShoot) > 0.2f)
	{
		if(!m_pTpsPlayer->GunIsEmpty() && m_pTpsPlayer->ReadyToShoot())
		{
			m_aBullets.Add(m_pTpsPlayer->Shoot());
		}
	}

	int enemiesNumber = m_aEnemies.GetCount();
	for(int enemiesCount = 0; enemiesCount < enemiesNumber; enemiesCount++)
	{
		m_pCollisionsManager->CheckPlayerEnemyViewField(m_pTpsPlayer, m_aEnemies.At(enemiesCount));
		if(m_aEnemies.At(enemiesCount)->GetCurrentState() == e_state_attack && (!m_aEnemies.At(enemiesCount)->GunIsEmpty()) && m_aEnemies.At(enemiesCount)->ReadyToShoot())
		{
			m_aBullets.Add(m_aEnemies.At(enemiesCount)->Shoot());
		}
	}

	for(int bulletCount = 0; bulletCount < m_aBullets.GetCount(); bulletCount++) // for each bullet
	{
		m_pCollisionsManager->CheckBulletCollisionShapeCollision(m_aBullets.At(bulletCount));
		m_pCollisionsManager->CheckBulletCharacterCollision(m_aBullets.At(bulletCount), m_pTpsPlayer);
		for(int enemiesCount = 0; enemiesCount < m_aEnemies.GetCount(); enemiesCount++)
		{
			m_pCollisionsManager->CheckBulletCharacterCollision(m_aBullets.At(bulletCount), m_aEnemies.At(enemiesCount));
			if(!m_aEnemies.At(enemiesCount)->isAlive())
			{
				CShTPSEnemy * enemy = m_aEnemies.At(enemiesCount);
				m_aEnemies.Remove(enemiesCount);
				//delete enemy;
			}
		}
		if(!m_aBullets.At(bulletCount)->isMoving())
		{
			m_aBullets.At(bulletCount)->GetOrigin()->Reload(m_aBullets.At(bulletCount));
			m_aBullets.Remove(bulletCount);
		}
	}

	m_pTpsPlayer->Update(dt);
	m_aBullets.ElementsUpdate(dt);
	m_aEnemies.ElementsUpdate(dt);
}