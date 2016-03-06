#include "CShPluginGame.h"

BEGIN_DERIVED_CLASS(CShPluginGame, CShPlugin)
	// ...
END_CLASS()


// Inputs to move and turn
ShInput *					g_pInputUp				= shNULL;
ShInput *					g_pInputLeft			= shNULL;
ShInput *					g_pInputRight			= shNULL;
ShInput *					g_pInputShoot			= shNULL;


ShInput *					g_pInputZ				= shNULL;
ShInput *					g_pInputQ				= shNULL;
ShInput *					g_pInputS				= shNULL;
ShInput *					g_pInputD				= shNULL;

//Camera
ShInput *					g_pInputPlus 			= shNULL;
ShInput *					g_pInputMinus			= shNULL;
ShInput *					g_pInputC				= shNULL;



/**
 * Constructor
 */
CShPluginGame::CShPluginGame(void)
: CShPlugin(CShIdentifier("TPS"))
, m_levelIdentifier(GID(NULL))
, m_aBackground()
, m_pTpsPlayer(new CShTPSPlayer())
, m_pCollisionsManager(new CShTPSCollisionsManager())
, m_pTpsCamera(new CShTPSCamera())
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

	m_pTpsCamera->Initialize();

	m_pCollisionsManager->Initialize(m_levelIdentifier);

	//create inputs
	g_pInputUp = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_up, 0.5f);
	g_pInputRight = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_right, 0.5f);
	g_pInputLeft = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_left, 0.5f);
	g_pInputShoot = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_space, 0.5f);
	
	g_pInputZ = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_z, 0.5f);
	g_pInputQ = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_q, 0.5f);
	g_pInputS = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_s, 0.5f);
	g_pInputD = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_d, 0.5f);

	g_pInputPlus = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_num_plus, 0.5f);
	g_pInputMinus = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_num_minus, 0.5f);
	g_pInputC = ShInput::CreateInputJustPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_c, 0.5f);

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
		
		ShEntity2 * pEnemySprite;
		pEnemySprite = ShEntity2::Find(levelIdentifier, CShIdentifier(enemyIdentifier));
		ShEntity3 * pEnemyModel = shNULL;
		if(shNULL == pEnemySprite) // if there is no 2D sprite, the game searches for a 3D model, and creates its 2D equivalent to manage collision between 2D stuff
		{
			pEnemyModel = ShEntity3::Find(levelIdentifier, CShIdentifier(enemyIdentifier));
			if(shNULL != pEnemyModel)
			{
				CShString enemyIdentifierForced2D(ENEMY_SPRITE_NAME);
				enemyIdentifierForced2D += "forced_2D_";
				enemyIdentifierForced2D += CShString::FromInt(nbEnemies);
				pEnemySprite = ShEntity2::Create(levelIdentifier, CShIdentifier(enemyIdentifierForced2D), GID(layer_default), CShIdentifier("tps"), CShIdentifier("enemy"), CShVector3(0.0f,0.0f,1.0f), CShEulerAngles(0.0f, 0.0f, 0.0f), CShVector3(1.0f, 1.0f, 1.0f));
			}
		}
		if(shNULL == pEnemySprite) // if there is no more enemies in the level we stop the research
		{
			searchEnemies = false;
		}
		else
		{
			CShTPSGun * pEnemyGun = new CShTPSGun(DESERT_EAGLE_POWER, CShString(DESERT_EAGLE_NAME), DESERT_EAGLE_FIRERATE);
			CShTPSEnemy * enemy = new CShTPSEnemy();
			enemy->Initialize(m_levelIdentifier, pEnemyGun, pEnemySprite, enemyCharacterControlleridentifier, pEnemyModel);
			m_aEnemies.Add(enemy);
		}
	}
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
	if (ShInput::GetValue(g_pInputPlus) > 0.2f)
	{
		m_pTpsCamera->FovInc();
	}

	if (ShInput::GetValue(g_pInputMinus) > 0.2f)
	{
		m_pTpsCamera->FovDec();
	}


	if (ShInput::GetValue(g_pInputC) > 0.2f)
	{
		m_pTpsCamera->SwitchCameraStyle();
	}



	// Change the walk speed/direction
	if (ShInput::GetValue(g_pInputUp) > 0.2f || ShInput::GetValue(g_pInputZ) > 0.2f)
	{
		m_pTpsPlayer->SetSpeed(PLAYER_DEFAULT_SPEED);
		m_pTpsPlayer->SwitchToAnimationRun();
	}
	else if (ShInput::GetValue(g_pInputS) > 0.2f)
	{
		m_pTpsPlayer->SetSpeed(-(PLAYER_DEFAULT_SPEED/2.0f));
		m_pTpsPlayer->SwitchToAnimationRun();
	}
	else
	{
		m_pTpsPlayer->SetSpeed(0.0f);
		m_pTpsPlayer->SwitchToAnimationIdle();
	}

	if (ShInput::GetValue(g_pInputLeft) > 0.2f || ShInput::GetValue(g_pInputQ) > 0.2f)
	{
		CShVector2 direction = m_pTpsPlayer->GetDirection();
		direction.Rotate(ROTATION_SPEED);
		m_pTpsPlayer->SetDirection(direction);
		ShEntity2::Rotate(m_pTpsPlayer->GetSprite(),CShEulerAngles(0, 0, ROTATION_SPEED));
		ShEntity3::Rotate(m_pTpsPlayer->GetModel(),CShEulerAngles(0, 0, ROTATION_SPEED));
	}
	
	if (ShInput::GetValue(g_pInputRight) > 0.2f || ShInput::GetValue(g_pInputD) > 0.2f)
	{
		CShVector2 direction = m_pTpsPlayer->GetDirection();
		direction.Rotate(-ROTATION_SPEED);
		m_pTpsPlayer->SetDirection(direction);
		ShEntity2::Rotate(m_pTpsPlayer->GetSprite(),CShEulerAngles(0, 0, -ROTATION_SPEED));
		ShEntity3::Rotate(m_pTpsPlayer->GetModel(),CShEulerAngles(0, 0, -ROTATION_SPEED));
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
	m_pTpsCamera->Update(m_pTpsPlayer->GetPosition(), m_pTpsPlayer->GetDirection());
}