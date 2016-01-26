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
			m_Bullets.Add(m_pTpsPlayer->Shoot());
		}
	}

	m_pTpsPlayer->Update();
	m_Bullets.ElementsUpdate(dt);

	m_pTpsPlayer->Render();
}