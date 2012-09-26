///--------------------------------------------------------------------------------------
/// @file	MrTestLogOutputFactory.h
/// @brief	Factory to create iLogOutput objects.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_LOG_OUTPUT_FACTORY_H)
#define MR_TEST_LOG_OUTPUT_FACTORY_H


#include "IMrTestLogOutput.h"
#include "IMrTestLogInitialiser.h"
#include "mr_sharedPtr.h"


namespace MrTest {

typedef mr_utils::SharedPtr<MrTest::ILogOutput> LogOutputSharedPtr;

//----------------------------------------------------------------------------------------
/// @brief	Class for creating iLogInitiser objects.
///
/// 
class LogOutputFactory {
public:

	///	@brief	Creates the appropriate iLogInitialiser.
	///
	/// @param	initialiser	Initialiser object. 
	static LogOutputSharedPtr Create( mr_utils::SharedPtr<MrTest::ILogInitialiser>& initialiser );
};


}// end namespace

#endif
