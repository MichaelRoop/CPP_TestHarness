///--------------------------------------------------------------------------------------
/// @file	mr_string.h
/// @brief	Cross char witdh defines for string class.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(DLL_REFLECTION_H)
#define DLL_REFLECTION_H

#include <string>
#include <vector>

namespace cppTest {

	std::vector<std::string> GetMethodNames(const std::wstring& dllName);


}

#endif