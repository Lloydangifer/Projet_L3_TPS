#include "Extension.h"

#include <ShSDK/ShSDK.h>

#include "../PluginGame/CShPluginGame.h"

static CShPluginGame plugin;

extern "C"
{

SAMPLE_EXTENSION_EXPORT void SH_EXTENSION_INITIALIZE(void)
{
	// Initialize the Rotate Plugin
	const CShIdentifier & topPoolIdentifier = CShPooledObjectManagerManager::GetInstance()->GetTopPoolIdentifier();
	plugin.Initialize(topPoolIdentifier);

	// Register the Rotate Plugin
	ShApplication::RegisterPlugin(&plugin);
}

SAMPLE_EXTENSION_EXPORT void SH_EXTENSION_RELEASE(void)
{
	// Release the Rotate Plugin
	plugin.Release();
}

}
