#include "Extension.h"

#include <ShSDK/ShSDK.h>

#include "../PluginGame/CShPluginGame.h"

static CShPluginGame plugin;

extern "C"
{

TPS_EXTENSION_EXPORT void ExtensionInitialize(void)
{
	// Initialize the Rotate Plugin
	const CShIdentifier & topPoolIdentifier = CShPooledObjectManagerManager::GetInstance()->GetTopPoolIdentifier();
	plugin.Initialize(topPoolIdentifier);

	// Register the Rotate Plugin
	ShApplication::RegisterPlugin(&plugin);
}

TPS_EXTENSION_EXPORT void ExtensionRelease(void)
{
	// Release the Rotate Plugin
	plugin.Release();
}

}
