#include "CShPluginGame.h"

BEGIN_DERIVED_CLASS(CShPluginGame, CShPlugin)
	// ...
END_CLASS()

/**
 * Constructor
 */
CShPluginGame::CShPluginGame(void)
: CShPlugin(CShIdentifier("TPS"))
, m_levelIdentifier(GID(NULL))
, m_pBackground(shNULL)
, m_pPlayer(shNULL)
, m_fScale(0.0f)
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
void CShPluginGame::OnPlayStart(void)
{

	m_pBackground = ShEntity2::Find(m_levelIdentifier, CShIdentifier("sprite_tps_background"));
	SH_ASSERT(shNULL != m_pBackground);

	m_pPlayer = ShEntity2::Find(m_levelIdentifier, CShIdentifier("sprite_tps_player"));
	SH_ASSERT(shNULL != m_pPlayer);

	//create inputs
	ShInput * up = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_up, 0.5f);
	ShInput * right = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_right, 0.5f);
	ShInput * left = ShInput::CreateInputPressed(ShInput::e_input_device_keyboard, ShInput::e_input_device_control_pc_key_left, 0.5f);
}

/**
 * Called when the plugin is stopped
 */
void CShPluginGame::OnPlayStop(void)
{
	// nothing here
}

/**
 * Called when the plugin is paused
 */
void CShPluginGame::OnPlayPause(void)
{
	// nothing here
}

/**
 * Called when the plugin is resumed
 */
void CShPluginGame::OnPlayResume(void)
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

}