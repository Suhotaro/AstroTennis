#pragma once

#ifdef RP_LIBS_EXPORTS
	#define RP_LIBS_API __declspec(dllexport)
#else
	#define RP_LIBS_API __declspec(dllimport)
#endif