#pragma once
///--------------------------------------------------------------------------------------
/// @file	ManagedTestCaseData.h
/// @brief	Managed Holder for test case execution results data
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2012 Michael Roop
///--------------------------------------------------------------------------------------

namespace MrTestGuiRunner {

using namespace System;
using namespace System::Runtime::InteropServices;

///--------------------------------------------------------------------------------------
///	@brief	Holder for test case execution results data
///--------------------------------------------------------------------------------------

public ref class ManagedTestCaseData {

public:

	///// @brief	Status indicator for the test case.
	enum class TestCaseStatus : int {
		NONE,					///< No status. Default
		DISABLED,				///< Test exists but marked disabled in script
		NOT_FOUND,				///< Test does not exist
		SUCCESS,				///< Successful
		FAIL_SETUP,				///< Failed on test setup
		FAIL_TEST,				///< Failed on test
		FAIL_CLEANUP,			///< Failed on test teardown
		FAIL_FIXTURE_SETUP,		///< Failed on Fixture setup
		FAIL_FIXTURE_TEARDOWN	///< Failed on Fixture teardown

	};

	TestCaseStatus	Status;			///< Status of the test case.
	String^		FixtureName;		///< Fixture name.
	String^		Name;				///< Test name.
	String^		Description;		///< Test description.
	//String^	m_args;				///< Test arguments.
	String^		MsgBuffer;			///< Short message buffer.
	//String^		EmbeddedMsgBuffer;	///< Used internally to create embedded messages // not useful
	String^		VerboseBuffer;		///< Verbose message buffer.
	long long	SetupTime;			///< Setup time in ms.
	long long	ExecTime;			///< Test time in ms.
	long long	CleanupTime;		///< Cleanup time in ms.
};

} // end namespace MrTestGuiRunner

