///--------------------------------------------------------------------------------------
/// @file	MrTestLogInitialiserFactory.h
/// @brief	Factory to create iLogInitialiser objects.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_LOG_INITIALISER_FACTORY_H)
#define MR_TEST_LOG_INITIALISER_FACTORY_H


#include "IMrTestLogInitialiser.h"
#include "mr_string.h"
#include "mr_sharedPtr.h"


namespace MrTest {

typedef mr_utils::SharedPtr<MrTest::ILogInitialiser> LogInitialiserSharedPtr;

//----------------------------------------------------------------------------------------
/// @brief	Class for creating iLogInitiser objects.
///
/// 
class LogInitialiserFactory {
public:

	///	@brief	Creates the appropriate iLogInitialiser.
	///
	/// @param	configFileName	Configuration file name. 
	/// @param	configFileType	Configuration file type. 
	/// @param	section			Configuration file section.
	static LogInitialiserSharedPtr Create( 
		const mr_utils::mr_string&	configFileName, 
		const mr_utils::mr_string&	configFileType, 
		const mr_utils::mr_string&	section 
	);


	/// @todo	Review this - different object versus reuse
	///	@brief	Creates the appropriate iLogInitialiser without a section
	///
	/// @param	configFileName	Configuration file name. 
	/// @param	configFileType	Configuration file type. 
	/// @param	section			Configuration file section.
	static LogInitialiserSharedPtr Create( 
		const mr_utils::mr_string&	configFileName, 
		const mr_utils::mr_string&	configFileType 
	);
};



}// end namespace

#endif
