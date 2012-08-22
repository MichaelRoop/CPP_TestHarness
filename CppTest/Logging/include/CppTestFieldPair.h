///--------------------------------------------------------------------------------------
/// @file	CppTestFieldPair.h
/// @brief	Data column information type.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_FIELD_PAIR_H)
#define CPP_TEST_FIELD_PAIR_H

#include "mr_string.h"
#include <vector>


namespace CppTest {

/// @brief Typedef of the basic pair that defines the name and type strings of a SQL field.
typedef std::pair<mr_utils::mr_string,mr_utils::mr_string> FieldPair;


/// @brief	Typedef of a vector of the FieldPair.
typedef std::vector< std::pair<mr_utils::mr_string,mr_utils::mr_string> > FieldVector;


} // end namespace

#endif
