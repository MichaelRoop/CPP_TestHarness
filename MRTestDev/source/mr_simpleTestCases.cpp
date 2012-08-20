//
//
//
//#include "mr_case.h"
//#include "mr_testMacros.h" // change test
//#include "mr_iostream.h"
//
//
////#include <Windows.h> //temp for testing timer
//
//class testCase1 : public mr_test::testCase
//{
//public:
//
//	testCase1( const mr_utils::mr_string& testName, const mr_utils::mr_string& argStr ) 
//		: mr_test::testCase( testName, argStr )
//	{
//	}
//
//	bool setup()
//	{
//		//::Sleep( 2100 );
//
//		mr_cout << this->name() << L(" - setup") << std::endl;
//		return true;
//	}
//
//	bool test()
//	{
//		mr_cout << this->name() << L(" - test") << std::endl;
//		
//		//::Sleep( 75 );
//
//		return true;
//	}
//		
//	bool cleanup()
//	{
//		//::Sleep( 510 );
//
//		mr_cout << this->name() << L(" - cleanup") << std::endl;
//		return true;
//	}
//
//};
//
//
//
//MAKE_CASE_DESC( TC1, instTC1, testCase1, L("Desc of test case") )
//MAKE_CASE( TC3, instTC3, testCase1 )
//
