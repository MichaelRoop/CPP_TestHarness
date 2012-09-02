// dllmain.cpp : Defines the entry point for the DLL application.

#if defined(WIN32)
#	define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#	include <windows.h>
#endif

#include <cstdio>

#include "mr_util_str_token_tests.h"
#include "mr_util_str_trim_tests.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved ) { 
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		printf("-----------------------------DLL_PROCESS_ATTACH - Utils Test Cases\n");
		{
			/*
			REGISTER_FIXTURE_MAIN(TokenizerTests1);
			REGISTER_FIXTURE_MAIN(TokenizerTests2);
			REGISTER_FIXTURE_MAIN(UtilStrTrimTests);
			*/
		}
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		printf("-----------------------------DLL_PROCESS_DETACH - Utils Test Cases\n");
		break;
	}
	return TRUE;
}

