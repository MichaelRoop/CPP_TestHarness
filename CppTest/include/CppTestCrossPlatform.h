#if !defined(CPP_TEST_CROSS_PLATFORM_H)
#define CPP_TEST_CROSS_PLATFORM_H
//
//#include "mr_string.h"
//#include "mr_sstream.h"
//#include "mr_exception.h"
//#include "mr_singleton.h"
//#include "mr_fstream.h"

#	define CPPTESCASE_API
#	define CPPTESCASE_EXP_TEMPLATE


//#if defined(WIN32) 
//	#if defined(CPPTESTCASE_EXPORTS)
//		#pragma message("Exporting CppTestCase DLL Classes")
//		#define CPPTESCASE_API __declspec(dllexport)
//		#define CPPTESCASE_EXP_TEMPLATE
//	#else
//		#pragma message("Importing CppTestCase DLL Classes")
//		#define CPPTESCASE_API __declspec(dllimport)
//		#define CPPTESCASE_EXP_TEMPLATE extern
//	#endif
//
//   //disable warnings on 255 char debug symbols
//    #pragma warning (disable : 4786)
//   //disable warnings on extern before template instantiation
//    #pragma warning (disable : 4231)
//#else
//#	pragma message("*** WIN32 Not defined ***")
//#	define CPPTESCASE_API
//#	define CPPTESCASE_EXP_TEMPLATE
//#endif




//
//
//#if defined(WIN32)
//	#ifdef EXPORT_CPP_TEST_CLASSES
//		#pragma message("Exporting DLL Classes")
//		#define DLL_EXP_IMP __declspec(dllexport)
//		#define EXP_TEMPLATE
//	#else
//		#pragma message("Importing DLL Classes")
//		#define DLL_EXP_IMP __declspec(dllimport)
//		#define EXP_TEMPLATE extern
//	#endif
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
//#else
//	#define DLL_EXP_IMP
//	#define EXP_TEMPLATE
//#endif
//
//
//
//
//
#endif
