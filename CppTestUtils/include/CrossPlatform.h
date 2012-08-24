#if !defined(CPP_UTILS_CROSS_PLATFORM_H)
#define CPP_UTILS_CROSS_PLATFORM_H

#include <string>
//#include <sstream>
#include <iostream>


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




#if defined(WIN32) 
	#if defined(CPPTESTUTILS_EXPORTS)
		#pragma message("Exporting CppTestUtils DLL Classes")
		#define CPPTESTUTILS_API __declspec(dllexport)
		#define EXP_TEMPLATE
	#else
		#pragma message("Importing CppTestUtils DLL Classes")
		#define CPPTESTUTILS_API __declspec(dllimport)
		#define EXP_TEMPLATE extern
	#endif

   //disable warnings on 255 char debug symbols
    #pragma warning (disable : 4786)
   //disable warnings on extern before template instantiation
    #pragma warning (disable : 4231)

	// We will put the most common template classes here
	EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator<wchar_t>;
	EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator<char>;

	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >;
	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_string<char, std::char_traits<char>, std::allocator<char> >;




//
//   //disable warnings on 255 char debug symbols
//    #pragma warning (disable : 4786)
//   //disable warnings on extern before template instantiation
//    #pragma warning (disable : 4231)
//
//	// Needed to export any class members that are templates. Only seem to apply to windows
//	//std::basic_string depends on this allocator, so it must also be exported. Does not seem to apply to char_trait
//	//EXP_TEMPLATE template class DLL_EXP_IMP std::allocator<mr_utils::mr_char>;
//	//EXP_TEMPLATE template class DLL_EXP_IMP std::basic_string<mr_utils::mr_char, std::char_traits<mr_utils::mr_char>, std::allocator<mr_utils::mr_char> >;
//	//EXP_TEMPLATE template class DLL_EXP_IMP std::basic_stringstream<mr_utils::mr_char, std::char_traits<mr_utils::mr_char>, std::allocator<mr_utils::mr_char> >;
//
//
//	EXP_TEMPLATE template class DLL_EXP_IMP std::allocator<wchar_t>;
//	EXP_TEMPLATE template class DLL_EXP_IMP std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >;
//	EXP_TEMPLATE template class DLL_EXP_IMP std::basic_stringstream<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >;
//
//	EXP_TEMPLATE template class DLL_EXP_IMP std::allocator<char>;
//	EXP_TEMPLATE template class DLL_EXP_IMP std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
//	EXP_TEMPLATE template class DLL_EXP_IMP std::basic_stringstream<char, std::char_traits<char>, std::allocator<char> >;
//
//	// mr_fstream
//	EXP_TEMPLATE template class DLL_EXP_IMP std::basic_filebuf<wchar_t, std::char_traits<wchar_t> >;
//	EXP_TEMPLATE template class DLL_EXP_IMP std::basic_ifstream<wchar_t, std::char_traits<wchar_t> >;
//	EXP_TEMPLATE template class DLL_EXP_IMP std::basic_ofstream<wchar_t, std::char_traits<wchar_t> >;
//
//
//	EXP_TEMPLATE template class DLL_EXP_IMP std::basic_filebuf<char, std::char_traits<char> >;
//	EXP_TEMPLATE template class DLL_EXP_IMP std::basic_ifstream<char, std::char_traits<char> >;
//	EXP_TEMPLATE template class DLL_EXP_IMP std::basic_ofstream<char, std::char_traits<char> >;
//
//	EXP_TEMPLATE class DLL_EXP_IMP std::exception;
//	EXP_TEMPLATE class DLL_EXP_IMP mr_utils::mr_exception;
//	EXP_TEMPLATE class DLL_EXP_IMP mr_utils::singleton;
//
//
//	//DLL_EXP_IMP bool mr_utils::MrTokenize;
//
//
//
//	//EXP_TEMPLATE template class DLL_EXP_IMP mr_exception;
//
//	//DLL_EXP_IMP mr_exception;
//
//
//
//
#else
	#define CPPTESTUTILS_EXPORTS
	#define EXP_TEMPLATE
#endif
//
//
//
//
//
#endif
