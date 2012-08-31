#if !defined(CPP_TEST_UTILS_DEFINES_H)
#define CPP_TEST_UTILS_DEFINES_H

#include <string>
#include <iostream>

#include <vector>

// Think it applies to both nix and win32
//#if defined(WIN32) 
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
//#else
//#	pragma message("*** WIN32 Not defined ***")
//#	define CPPTESTUTILS_EXPORTS
//#	define EXP_TEMPLATE
//#endif

	// TODO - figure out a way to get the string npos exported. It will cause link failures in with classes using the npos or substring

#endif
