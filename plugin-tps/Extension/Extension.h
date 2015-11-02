#ifndef __EXTENSION_H
#define __EXTENSION_H

#if defined(_WIN32) 
#	if defined(ExtensionTPS_EXPORTS)
#		define SAMPLE_EXTENSION_EXPORT __declspec(dllexport)
#	else
#		define SAMPLE_EXTENSION_EXPORT __declspec(dllimport)
#	endif // ExtensionTPS_EXPORTS
#else // defined(_WIN32)
#	define SAMPLE_EXTENSION_EXPORT
#endif

#define SH_EXTENSION_INITIALIZE		PluginInitialize
#define SH_EXTENSION_RELEASE		PluginRelease

extern "C"
{
	SAMPLE_EXTENSION_EXPORT void	SH_EXTENSION_INITIALIZE		(void);
	SAMPLE_EXTENSION_EXPORT void	SH_EXTENSION_RELEASE		(void);
}

#endif // __EXTENSION_H