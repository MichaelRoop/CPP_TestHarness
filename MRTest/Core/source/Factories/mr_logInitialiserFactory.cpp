///--------------------------------------------------------------------------------------
/// @file	mr_logInitialiserFactory.cpp
/// @brief	Factory to create iLogInitialiser objects.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_logInitialiserFactory.h"
#include "mr_iniLogInitialiser.h"
#include "mr_exception.h"
#include "mr_sstream.h"
#include "mr_defines.h"


namespace mr_test
{

logInitialiserSharedPtr logInitialiserFactory::create( 
	const std::string&			configFileName, 
	const mr_utils::mr_string&	configFileType, 
	const mr_utils::mr_string&	section 
)
{
	logInitialiserSharedPtr	initialiser;

	if (configFileType.compare( L("INI") ) == 0)
	{
		initialiser = new iniLogInitialiser( configFileName, section );
	}
	//else if (configFileType.compare( L("XML") ) == 0)
	//{
	//	mr_utils::mr_exception::assertCondition( false, FL, L("Not implemented") );
	//}
	else
	{
		mr_utils::mr_stringstream os;
		os << L("Illegal initialiser file type:") << configFileType << L(" Allowed types are 'INI'");
		mr_utils::mr_exception::assertCondition( false, FL, os.str() );
	}

	if (!initialiser->load())
	{
		mr_utils::mr_stringstream os;
		os << configFileName.c_str() << L(" failed to load");
		mr_utils::mr_exception::assertCondition( false, FL, os.str() );
	}
	return initialiser;
}


logInitialiserSharedPtr logInitialiserFactory::create( 
	const std::string&			configFileName, 
	const mr_utils::mr_string&	configFileType 
)
{
	/// @todo review this - temp to get an init file to only access test list.
	return logInitialiserFactory::create( configFileName, configFileType, mr_utils::mr_string() );
}



}// end namespace

