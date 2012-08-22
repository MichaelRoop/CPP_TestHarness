///--------------------------------------------------------------------------------------
/// @file	mr_logFactory.h
/// @brief	Factory to create itestLog objects.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_LOG_FACTORY_H)
#define MR_LOG_FACTORY_H


#include "mr_iTestLog.h"
#include "mr_iLogInitialiser.h"
#include "mr_sharedPtr.h"


namespace mr_test
{

typedef mr_utils::SharedPtr<mr_test::iTestLog> logSharedPtr;

//----------------------------------------------------------------------------------------
/// @brief	Class for creating iLogInitiser objects.
///
/// 
class logFactory
{
public:

	///	@brief	Creates the appropriate iLogInitialiser.
	///
	/// @param	configFileName	Configuration file name. 
	/// @param	configFileType	Configuration file type. 
	/// @param	section			Configuration file section.
	static logSharedPtr create( 
		const std::string&			configFileName, 
		const mr_utils::mr_string&	configFileType, 
		const mr_utils::mr_string&	section 
	);

private:

	/// @brief	Constructor.
	///
	/// @param	output			A SharedObject logOutput object.
	/// @param	summaryLog		A SharedObject summary logger.
	/// @param	initialiser		A SharedObject reference to an iLogInitialiser.
	static logSharedPtr create(
			mr_utils::SharedPtr<iLogOutput>&		output, 
			mr_utils::SharedPtr<iTestLog>&			summaryLog, 
			mr_utils::SharedPtr<iLogInitialiser>&	initialiser 
		);
};



}// end namespace

#endif
