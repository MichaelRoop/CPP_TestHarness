//
//#include "mr_case.h"
//#include "mr_testMacros.h"
//#include "mr_threadObj.h"
//#include "mr_lockedWriteOut.h"
//#include "mr_event.h"
//#include "mr_threadFunctions.h"
//
//
//class JoinAndBreakTestThread : public mr_threads::mr_threadObj
//{
//protected:
//
//	virtual void Run()
//	{
//		mr_threads::LockedWriteLineToConsole( L("Thread::Starting Run - wait on event") );
//		m_event.Wait();
//		mr_threads::LockedWriteLineToConsole( L("Thread::Event signaled - dropping out of Run") );
//	}
//
//	virtual void Break()
//	{
//		m_event.Signal();
//	}
//
//private:
//
//	mr_threads::mr_event m_event;
//
//};
////-----------------------------------------------------------
//
//
///// @brief	Base test case.
//class _mr_joinAndBreakTestBase : public mr_test::testCase
//{
//public:
//	_mr_joinAndBreakTestBase(  const mr_utils::mr_string& name, const mr_utils::mr_string& desc )
//		: mr_test::testCase( name, desc )
//	{
//	}
//
//
//	void RunSequence()	
//	{ 
//		mr_threads::LockedWriteLineToConsole( L("----TestCaseBase::Starting thread") );
//		m_th1.Start();
//
//		mr_threads::LockedWriteLineToConsole( L("----TestCaseBase::Killing time after start") );
//		mr_threads::MRSleep( 3000 );
//
//		mr_threads::LockedWriteLineToConsole( L("----TestCaseBase::Calling BreakAndJoin on thread") );
//		m_th1.BreakAndJoin();
//	}
//
//private:
//
//	JoinAndBreakTestThread m_th1;
//};
//
//
//
//_DECL_TEST_( _mr_joinAndBreakTest1, _mr_joinAndBreakTestBase)
//	bool test()	
//	{ 
//		this->RunSequence();
//		return true;
//	}
//_REG_TEST_( THR_1_2_1, instTHR_1_2_1, _mr_joinAndBreakTest1, L("Join and break test") )
//
//
//_DECL_TEST_( _mr_joinAndBreakTest2, _mr_joinAndBreakTestBase)
//	bool test()	
//	{ 
//		mr_threads::LockedWriteLineToConsole( L("TestCase::First sequence") );
//		this->RunSequence();
//		mr_threads::LockedWriteLineToConsole( L("TestCase::Second sequence") );
//		this->RunSequence();
//		return true;
//	}
//_REG_TEST_( THR_1_2_2, instTHR_1_2_2, _mr_joinAndBreakTest2, L("Join and break test - with restart") )
//
