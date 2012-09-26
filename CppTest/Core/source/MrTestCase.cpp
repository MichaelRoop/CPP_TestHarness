///--------------------------------------------------------------------------------------
/// @file	MrTestCase.cpp
/// @brief	Holder for test case execution results data
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.5
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "MrTestCase.h"

namespace MrTest {


Case::Case(
	const mr_utils::mr_string& fixtureName, 
	const mr_utils::mr_string& name, 
	const mr_utils::mr_string& desc) : 	
	ICase(fixtureName, name, desc) {
}


Case::~Case() {
}


void Case::Reset() {
	this->Status = Case::ST_NONE;
	//this->m_args.clear();
	mr_utils::ResetStringStream(this->MsgBuffer);
	mr_utils::ResetStringStream(this->EmbeddedMsgBuffer);
	mr_utils::ResetStringStream(this->VerboseBuffer);
	this->SetupTime = 0;
	this->ExecTime = 0;
	this->CleanupTime = 0;
}

} // end namespace
