///--------------------------------------------------------------------------------------
/// @file	CppTestLogInitialiserFactory.cpp
/// @brief	Factory to create iLogInitialiser objects.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestLogInitialiserFactory.h"
#include "CppTestIniLogInitialiser.h"
#include "mr_exception.h"
#include "mr_sstream.h"
#include "mr_defines.h"


namespace MrTest {

LogInitialiserSharedPtr LogInitialiserFactory::Create( 
	const mr_utils::mr_string&	configFileName, 
	const mr_utils::mr_string&	configFileType, 
	const mr_utils::mr_string&	section 
) {
	LogInitialiserSharedPtr	initialiser;

	if (configFileType.compare(_L_("INI")) == 0) {
		initialiser = new MrTest::IniLogInitialiser(configFileName, section);
	}
	//else if (configFileType.compare( L("XML") ) == 0)
	//{
	//	mr_utils::mr_exception::assertCondition( false, FL, L("Not implemented") );
	//}
	else {
		mr_utils::mr_stringstream os;
		os << _L_("Illegal initialiser file type:") << configFileType << _L_(" Allowed types are 'INI'");
		mr_utils::mr_exception::assertCondition( false, FL, os.str() );
	}

	if (!initialiser->Load()) {
		mr_utils::mr_stringstream os;
		os << configFileName.c_str() << _L_(" failed to load");
		mr_utils::mr_exception::assertCondition(false, FL, os.str());
	}
	return initialiser;
}


LogInitialiserSharedPtr LogInitialiserFactory::Create( 
	const mr_utils::mr_string&	configFileName, 
	const mr_utils::mr_string&	configFileType 
) {
	/// @todo review this - temp to get an init file to only access test list.
	return LogInitialiserFactory::Create(configFileName, configFileType, mr_utils::mr_string());
}

}// end namespace

