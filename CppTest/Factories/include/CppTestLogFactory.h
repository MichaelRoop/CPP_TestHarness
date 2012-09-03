///--------------------------------------------------------------------------------------
/// @file	CppTestLogFactory.h
/// @brief	Factory to create itestLog objects.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_LOG_FACTORY_H)
#define CPP_TEST_LOG_FACTORY_H

#include "ICppTestLog.h"
#include "ICppTestLogInitialiser.h"
#include "mr_sharedPtr.h"


namespace MrTest {

typedef mr_utils::SharedPtr<MrTest::ILog> LogSharedPtr;

//----------------------------------------------------------------------------------------
/// @brief	Class for creating iLogInitiser objects.
///
/// 
class LogFactory {
public:

	///	@brief	Creates the appropriate iLogInitialiser.
	///
	/// @param	configFileName	Configuration file name. 
	/// @param	configFileType	Configuration file type. 
	/// @param	section			Configuration file section.
	static LogSharedPtr Create( 
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
	static LogSharedPtr Create(
			mr_utils::SharedPtr<MrTest::ILogOutput>&		output, 
			mr_utils::SharedPtr<MrTest::ILog>&			summaryLog, 
			mr_utils::SharedPtr<MrTest::ILogInitialiser>&	initialiser 
		);
};


}// end namespace

#endif
