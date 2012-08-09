///--------------------------------------------------------------------------------------
/// @file	mr_logInitialiserFactory.h
/// @brief	Factory to create iLogInitialiser objects.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_LOG_INITIALISER_FACTORY_H)
#define MR_LOG_INITIALISER_FACTORY_H


#include "mr_iLogInitialiser.h"
#include "mr_string.h"
#include "mr_sharedPtr.h"


namespace mr_test
{

typedef mr_utils::SharedPtr<mr_test::iLogInitialiser> logInitialiserSharedPtr;

//----------------------------------------------------------------------------------------
/// @brief	Class for creating iLogInitiser objects.
///
/// 
class logInitialiserFactory
{
public:

	///	@brief	Creates the appropriate iLogInitialiser.
	///
	/// @param	configFileName	Configuration file name. 
	/// @param	configFileType	Configuration file type. 
	/// @param	section			Configuration file section.
	static logInitialiserSharedPtr create( 
		const std::string&			configFileName, 
		const mr_utils::mr_string&	configFileType, 
		const mr_utils::mr_string&	section 
	);


	/// @todo	Review this - different object versus reuse
	///	@brief	Creates the appropriate iLogInitialiser without a section
	///
	/// @param	configFileName	Configuration file name. 
	/// @param	configFileType	Configuration file type. 
	/// @param	section			Configuration file section.
	static logInitialiserSharedPtr create( 
		const std::string&			configFileName, 
		const mr_utils::mr_string&	configFileType 
	);
};



}// end namespace

#endif
