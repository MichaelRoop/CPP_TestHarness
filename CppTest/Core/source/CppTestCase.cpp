///--------------------------------------------------------------------------------------
/// @file	CppTestCase.cpp
/// @brief	Holder for test case execution results data
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.5
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestCase.h"
#include "mr_exception.h"
#include "mr_defines.h"

namespace CppTest {


Case::Case() {
}


Case::Case(const mr_utils::mr_string& name, const mr_utils::mr_string& desc) 
:	ICase() {
	this->Name = name;
	this->Description = desc;
	this->SetupTime = 0;
	this->ExecTime = 0;
	this->CleanupTime = 0;
	this->Status = ST_NONE; 
}


Case::~Case() {
}


Case::Case(const Case& copy) {
	this->Status = copy.Status;
	this->Name = copy.Name;
	this->Description = copy.Description;
	//this->m_args.clear();  // TODO - figure out what to do with args
	this->MsgBuffer << copy.MsgBuffer.rdbuf();
	this->VerboseBuffer << copy.VerboseBuffer.rdbuf();
	this->SetupTime = copy.SetupTime;
	this->ExecTime = copy.ExecTime;
	this->CleanupTime = copy.CleanupTime;
}

void Case::Reset() {
	this->Status = Case::ST_NONE;
	//this->m_args.clear();
	mr_utils::ResetStringStream(this->MsgBuffer);
	mr_utils::ResetStringStream(this->VerboseBuffer);
	this->SetupTime = 0;
	this->ExecTime = 0;
	this->CleanupTime = 0;
}

} // end namespace
