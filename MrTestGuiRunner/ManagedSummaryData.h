#pragma once

namespace MrTestGuiRunner {

using namespace System;


public ref class ManagedSummaryData {
public:

	int	Success;			///< Counter for successful tests.
	int	FailFixtureSetup;	///< Counter tests that failed on fixture setup.
	int	FailSetup;			///< Counter tests that failed on setup.
	int	FailTest;			///< Counter tests that failed on test.
	int	FailTeardown;		///< Counter tests that failed on teardown.
	int	NotFound;			///< Counter tests not found.
	int	Disabled;			///< Counter tests not found.
	int	Total;				///< Counter tests not found.

};

}
