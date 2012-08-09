// Event tests are THR_2_0_n 

#include "mr_testMacros.h"
#include "mr_event.h"
#include "mr_compareFunctions.h"
#include "mr_lockedWriteOut.h"


//-------------------------------------------------------------------------------------
// Test manual event with Reset.
_DECL_TEST_( _mr_manEventTest1, mr_test::testCase)
	bool test()	
	{ 
		mr_threads::mr_event ev( false );
		ev.Signal();
		ev.Wait();
		ev.Reset();
		return mr_test::CompareEqual( mr_threads::EV_TIMEOUT, ev.Wait( 200 ), *this, L("Did not timeout") );
	}
_REG_TEST_( THR_2_0_1, instTHR_2_0_1, _mr_manEventTest1, L("Manual event test - Reset & timeout on next wait") )


//-------------------------------------------------------------------------------------
// Test manual event with no Reset.
_DECL_TEST_( _mr_manEventTest2, mr_test::testCase)
	bool test()	
	{ 
		mr_threads::mr_event ev( false );
		ev.Signal();
		ev.Wait();
		return mr_test::CompareEqual( mr_threads::EV_SIGNALED, ev.Wait( 200 ), *this, L("Not signaled") );
	}
_REG_TEST_( THR_2_0_2, instTHR_2_0_2, _mr_manEventTest2, L("Manual event test no reset - Drop through 2 waits") )


//-------------------------------------------------------------------------------------
// Test manual event with no Reset.
_DECL_TEST_( _mr_manEventTest3, mr_test::testCase)
	bool test()	
	{ 
		mr_threads::mr_event ev( false );
		return mr_test::CompareEqual( false, ev.IsSignaled(), *this, L("should not have been signaled") );
	}
_REG_TEST_( THR_2_0_3, instTHR_2_0_3, _mr_manEventTest3, L("Manual Event IsSignaled with on non-signaled event") )


//-------------------------------------------------------------------------------------
// Test IsSignaled with signaled event.
_DECL_TEST_( _mr_manEventTest4, mr_test::testCase)
	bool test()	
	{ 
		mr_threads::mr_event ev( false );
		ev.Signal();
		return mr_test::CompareEqual( true, ev.IsSignaled(), *this, L("should not have been signaled") );
	}
_REG_TEST_( THR_2_0_4, instTHR_2_0_4, _mr_manEventTest4, L("Manual Event IsSignaled with on non-signaled event") )



//=========================================================================================
// Auto event tests
//=========================================================================================

//-------------------------------------------------------------------------------------
// Test IsSignaled with no signal.
_DECL_TEST_( _mr_autoEventTest101, mr_test::testCase)
	bool test()	
	{ 
		mr_threads::mr_event ev;
		return mr_test::CompareEqual( false, ev.IsSignaled(), *this, L("should not have been signaled") );
	}
_REG_TEST_( THR_2_0_101, instTHR_2_0_101, _mr_autoEventTest101, L("Auto Event IsSignaled with on non-signaled event") )


//-------------------------------------------------------------------------------------
// Test IsSignaled with signaled event.
_DECL_TEST_( _mr_autoEventTest102, mr_test::testCase)
	bool test()	
	{ 
		mr_threads::mr_event ev;
		ev.Signal();
		return mr_test::CompareEqual( true, ev.IsSignaled(), *this, L("should not have been signaled") );
	}
_REG_TEST_( THR_2_0_102, instTHR_2_0_102, _mr_autoEventTest102, L("Auto Event IsSignaled with on non-signaled event") )






