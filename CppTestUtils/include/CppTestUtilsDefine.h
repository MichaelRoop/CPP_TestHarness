#if !defined(CPP_TEST_UTILS_DEFINES_H)
#define CPP_TEST_UTILS_DEFINES_H


#include <string>
//#include <sstream>
#include <iostream>

#include <vector>

//#include <xstring>

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

	// The order is important. Do not change
	EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator<char>;
	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_string<char, struct std::char_traits<char>, std::allocator<char> >;
	EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator< std::basic_string<char, struct std::char_traits<char>, std::allocator<char> > >;
	EXP_TEMPLATE template class CPPTESTUTILS_API std::vector< std::basic_string<char, struct std::char_traits<char>, std::allocator<char> > >;


	EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator<wchar_t>;
	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_string<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> >;
	EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator< std::basic_string<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> > >;
	EXP_TEMPLATE template class CPPTESTUTILS_API std::vector< std::basic_string<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> > >;


	// TODO try and figure out how to for string::npos to export

	//CPPTESTUTILS_API static const size_type  std::basic_string<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> >::npos;

//CPPTESTUTILS_API static const mr_utils::mr_string::size_type mr_utils::mr_string::npos;



/*

	// We will put the most common template classes here
	EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator<wchar_t>;
	EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator<char>;

	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_string<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> >;
	EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_string<char, struct std::char_traits<char>, std::allocator<char> >;

	//EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> >;
	//EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator<char, struct std::char_traits<char>, std::allocator<char> >;

	EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator< std::basic_string<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> > >;
	EXP_TEMPLATE template class CPPTESTUTILS_API std::vector< std::basic_string<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> > >;

	EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator< std::basic_string<char, struct std::char_traits<char>, std::allocator<char> > >;
	EXP_TEMPLATE template class CPPTESTUTILS_API std::vector< std::basic_string<char, struct std::char_traits<char>, std::allocator<char> > >;


	//EXP_TEMPLATE template class CPPTESTUTILS_API std::vector<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> >;
	//EXP_TEMPLATE template class CPPTESTUTILS_API std::vector<char, struct std::char_traits<char>, std::allocator<char> >;
	*/


//		std::allocator<char>::n:npos;

	//CPPTESTUTILS_API std::basic_string<char, struct std::char_traits<char>, std::allocator<char> >::size_type std::basic_string<char, struct std::char_traits<char>, std::allocator<char> >::npos;

	//CPPTESTUTILS_API  static const size_type npos;	// bad/missing length/position



//template std::string::size_type std::string::npos;
//template std::wstring::size_type std::wstring::npos;



//EXP_TEMPLATE int const std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class std::allocator<wchar_t> >::npos;


	//EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_string<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> >::npos;
	//EXP_TEMPLATE template class CPPTESTUTILS_API std::basic_string<char, struct std::char_traits<char>, std::allocator<char> >::npos;

	//// force export
	//EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator< std::basic_string<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> > >;
	//EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator< std::basic_string<char, struct std::char_traits<char>, std::allocator<char> > >;

	//// force export
	//EXP_TEMPLATE template class CPPTESTUTILS_API std::vector< std::basic_string<wchar_t, struct std::char_traits<wchar_t>, std::allocator<wchar_t> > >;
	//EXP_TEMPLATE template class CPPTESTUTILS_API std::vector< std::basic_string<char, struct std::char_traits<char>, std::allocator<char> > >;


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
#	pragma message("*** WIN32 Not defined ***")
#	define CPPTESTUTILS_EXPORTS
#	define EXP_TEMPLATE
#endif
//
//
//
//
//
#endif
