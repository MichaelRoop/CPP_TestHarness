///--------------------------------------------------------------------------------------
/// @file	mr_char.h
/// @brief	Cross char width char functions.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// @todo	Make char versions for trim functions.
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_CHAR_H) 
#define MR_CHAR_H


namespace mr_utils
{

#if defined(MR_USE_WIDE_STR)
	#pragma message("MR_USE_WIDE_STR defined")

	typedef wchar_t			mr_char;


	/// @brief	Variable with const string macro.
	#define L(str) L##str
#else
	typedef char			mr_char;


	/// @brief	Variable with const string macro.
	#define L( str ) str
#endif

/// @todo	Make char versions for trim functions.
//mr_string TrimRight( const mr_string& str );
//
//
//mr_string TrimLeft( const mr_string& str );
//
//
//mr_string Trim( const mr_string& str );


}






#endif
