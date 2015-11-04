#ifndef __EXTENSION_H
#define __EXTENSION_H

#if defined(_WIN32) 
#	if defined(ExtensionTPS_EXPORTS)
#		define TPS_EXTENSION_EXPORT __declspec(dllexport)
#	else
#		define TPS_EXTENSION_EXPORT __declspec(dllimport)
#	endif // ExtensionTPS_EXPORTS
#else // defined(_WIN32)
#	define TPS_EXTENSION_EXPORT
#endif

extern "C"
{
	TPS_EXTENSION_EXPORT void	ExtensionInitialize		(void);
	TPS_EXTENSION_EXPORT void	ExtensionRelease		(void);
}

#endif // __EXTENSION_H