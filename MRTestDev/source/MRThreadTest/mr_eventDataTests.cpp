// Event Data tests are THR_2_1_n 


#include "mr_testMacros.h"
#include "mr_dataEvent.h"
#include "mr_queuedDataEvent.h"
#include "mr_compareFunctions.h"



_DECL_TEST_( _mr_dataEventTest1, mr_test::testCase)
	bool test()	
	{ 
		mr_utils::mr_string target;
		mr_utils::mr_string source( L("This is a string") );

		mr_threads::mr_dataEvent<mr_utils::mr_string> dv;
		dv.Signal( source );
		dv.Wait( target );

		return mr_test::CompareEqual( source, target, this->getMsgBuffer());
	}
_REG_TEST_( THR_2_1_1, instTHR_2_1_1, _mr_dataEventTest1, L("Data event test - wait") )


_DECL_TEST_( _mr_dataEventTest2, mr_test::testCase)
	bool test()	
	{ 
		mr_utils::mr_string target;
		mr_utils::mr_string source( L("This is a string") );

		mr_threads::mr_dataEvent<mr_utils::mr_string> dv;
		dv.Signal( source );

		if (mr_test::CompareEqual( dv.IsSignaled( target ), true, this->getMsgBuffer()))
		{
			return mr_test::CompareEqual( source, target, this->getMsgBuffer());
		}
		return false;
	}
_REG_TEST_( THR_2_1_2, instTHR_2_1_2, _mr_dataEventTest2, L("Data event test - IsSignaled") )


