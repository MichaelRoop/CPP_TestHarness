//
//#include "mr_case.h"
//#include "mr_testMacros.h"
////#include "mr_compareFunctions.h"
//#include "mr_state.h"
//#include "mr_superState.h"  //temp
//
//
//#include "mr_iostream.h"
//
//
//// dummy for compile on dev
//struct dummyEvent
//{
//	unsigned int m_id;
//	unsigned int m_event;
//};
//
//class dummyState : public mr_sm::mr_state<dummyEvent>
//{
//public:
//	dummyState( unsigned int id ) : mr_sm::mr_state<dummyEvent>( id ) 
//	{
//	}
//
//protected:
//	virtual unsigned int OnState( const dummyEvent& /*_event*/ )
//	{
//		mr_cout << L("Dummy state OnState") << std::endl;
//		return 0;
//	}
//
//	virtual void OnEntry()
//	{
//		mr_cout << L("Dummy state OnEntry") << std::endl;
//	}
//
//	virtual void OnExit()
//	{
//		mr_cout << L("Dummy state OnExit") << std::endl;
//	}
//};
//
//
//class dummySuperState : public mr_sm::mr_superState<dummyEvent>
//{
//public:
//	dummySuperState( unsigned int id ) : mr_sm::mr_superState<dummyEvent>( id ) 
//	{
//	}
//
//protected:
//	virtual unsigned int OnState( const dummyEvent& /*_event*/ )
//	{
//		mr_cout << L("SSDummy state OnState") << std::endl;
//		return 0;
//	}
//
//	virtual void OnEntry()
//	{
//		mr_cout << L("SSDummy state OnEntry") << std::endl;
//	}
//
//	virtual void OnExit()
//	{
//		mr_cout << L("SSDummy state OnExit") << std::endl;
//	}
//};
//
//
//
//
//
//
////---------------------------------------------------------------------------------------
//// Test int compare.
//_DECL_TEST_( mrSMTest1, mr_test::testCase )
//	bool test()		
//	{ 
//		dummyState* st = new dummyState( 100 );
//
//		dummyEvent intV;
//		st->PulseState( intV );
//		//delete st;
//
//
//		dummySuperState* sst = new dummySuperState( 101 );
//		sst->AddState( st );
//		sst->SetDefaultState( 100 );
//		sst->PulseState( intV );
//
//		//delete st;
//
//
//		delete sst;
//
//
//
//		return true;
//		//return mr_test::VerbCompareEqual( FL, 100, 100, *this );
//	}
//_REG_TEST_( SM_1_1, instSM_1_1, mrSMTest1, L( "state machine test 1" ) )
//
//
