//// The following ifdef block is the standard way of creating macros which make exporting 
//// from a DLL simpler. All files within this DLL are compiled with the CPPTESTUTILS_EXPORTS
//// symbol defined on the command line. This symbol should not be defined on any project
//// that uses this DLL. This way any other project whose source files include this file see 
//// CPPTESTUTILS_API functions as being imported from a DLL, whereas this DLL sees symbols
//// defined with this macro as being exported.
//#ifdef CPPTESTUTILS_EXPORTS
//#define CPPTESTUTILS_API __declspec(dllexport)
//#else
//#define CPPTESTUTILS_API __declspec(dllimport)
//#endif
//
//// This class is exported from the CppTestUtils.dll
//class CPPTESTUTILS_API CCppTestUtils {
//public:
//	CCppTestUtils(void);
//	// TODO: add your methods here.
//};
//
//extern CPPTESTUTILS_API int nCppTestUtils;
//
//CPPTESTUTILS_API int fnCppTestUtils(void);
