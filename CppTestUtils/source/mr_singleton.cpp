///--------------------------------------------------------------------------------------
/// @file	mr_singleton.cpp
/// @brief	Base class that defines Singleton behavior.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_singleton.h"

namespace mr_utils {

	singleton::singleton() {
		this->Initialise();
	}


	singleton::singleton( const singleton& ) {
	}


	void singleton::Initialise() {
	}
	
} // end of namespace.
