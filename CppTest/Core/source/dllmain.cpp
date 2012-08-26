// dllmain.cpp : Defines the entry point for the DLL application.

#if defined(WIN32)
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
//// Windows Header Files:
#include <windows.h>

//#include <WinBase.h>
#endif

#include <cstdio>


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		printf("-----------------------------DLL_PROCESS_ATTACH\n");
		break;
	case DLL_THREAD_ATTACH:
		printf("-----------------------------DLL_THREAD_ATTACH\n");
		break;
	case DLL_THREAD_DETACH:
		printf("-----------------------------DLL_THREAD_ATTACH\n");
		break;
	case DLL_PROCESS_DETACH:
		printf("-----------------------------DLL_PROCESS_DETACH\n");
		break;
	}
	return TRUE;
}

