///--------------------------------------------------------------------------------------
/// @file	CppTestLogOutputFactory.h
/// @brief	Factory to create iLogOutput objects.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_LOG_OUTPUT_FACTORY_H)
#define CPP_TEST_LOG_OUTPUT_FACTORY_H


#include "mr_iLogOutput.h"
#include "mr_iLogInitialiser.h"
#include "mr_sharedPtr.h"


namespace CppTest {

typedef mr_utils::SharedPtr<mr_test::iLogOutput> LogOutputSharedPtr;

//----------------------------------------------------------------------------------------
/// @brief	Class for creating iLogInitiser objects.
///
/// 
class LogOutputFactory {
public:

	///	@brief	Creates the appropriate iLogInitialiser.
	///
	/// @param	initialiser	Initialiser object. 
	static LogOutputSharedPtr Create( mr_utils::SharedPtr<mr_test::iLogInitialiser>& initialiser );
};


}// end namespace

#endif
