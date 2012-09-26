//
//#include "mr_case.h"
//#include "mr_testMacros.h"
//#include "mr_compareFunctions.h"
//
//
////---------------------------------------------------------------------------------------
//// Test int compare.
//_DECL_TEST_( mrIntEqComp, mr_test::testCase )
//	bool test()		
//	{ 
//		return mr_test::VerbCompareEqual( FL, 100, 100, this->getVerboseBuffer() );
//	}
//_REG_TEST_( COMP_1_1, instCOMP_1_1, mrIntEqComp, L( "compare same ints" ) )
//
//
////---------------------------------------------------------------------------------------
//// Test not equal int compare.
//_DECL_TEST_( mrIntNotEqComp, mr_test::testCase )
//	bool test()		
//	{ 
//		return mr_test::VerbCompareNotEqual( FL, 100, 4234234, this->getVerboseBuffer());
//	}
//_REG_TEST_( COMP_1_2, instCOMP_1_2, mrIntNotEqComp, L( "Not equal int compare" ) )
//
//
////---------------------------------------------------------------------------------------
//// Test not equal int compare.
//_DECL_TEST_( mrIntVecEqComp, mr_test::testCase )
//	bool test()		
//	{ 
//		std::vector<int> expected;
//		expected.push_back( 1 );
//		expected.push_back( 6 );
//		expected.push_back( 345 );
//
//		std::vector<int> actual;
//		actual.push_back( 1 );
//		actual.push_back( 66 );
//		actual.push_back( 345 );
//
//		return mr_test::VerbCompareVecEqual( FL, expected, actual, this->getVerboseBuffer() );
//	}
//_REG_TEST_( COMP_1_3, instCOMP_1_3, mrIntVecEqComp, L( "compare same int vectors" ) )
//
//
////---------------------------------------------------------------------------------------
//// Test int compare failure.
//_DECL_TEST_( mrIntEqCompFail, mr_test::testCase )
//	bool test()		
//	{ 
//		return !mr_test::VerbCompareEqual( FL, 100, 38, this->getVerboseBuffer() );
//	}
//_REG_TEST_( COMP_3, instCOMP_3, mrIntEqCompFail, L( "Fail int comparison - shows error dump" ) )
//
//
////---------------------------------------------------------------------------------------
//// Test not equal int compare failure.
//_DECL_TEST_( mrIntNotEqCompFail, mr_test::testCase )
//	bool test()		
//	{ 
//		return !mr_test::VerbCompareNotEqual( FL, 100, 100, this->getVerboseBuffer() );
//	}
//_REG_TEST_( COMP_4, instCOMP_4, mrIntNotEqCompFail, L( "Fail Not equal int compare - shows error dump" ) )
//
//
//
////---------------------------------------------------------------------------------------
//// Test string compare.
//_DECL_TEST_( mrIntStrComp, mr_test::testCase )
//	bool test()		
//	{ 
//		return mr_test::VerbCompareEqual( FL, std::string( "Fred" ), std::string( "Fred" ), this->getVerboseBuffer() );
//	}
//_REG_TEST_( COMP_5_1, instCOMP_5_1, mrIntStrComp, L( "compare same strings" ) )
//
//
////---------------------------------------------------------------------------------------
//// Test string compare.
//_DECL_TEST_( mrIntStrCompFail, mr_test::testCase )
//	bool test()		
//	{ 
//		return mr_test::VerbCompareEqual( FL, std::string( "Fred" ), std::string( "George" ), this->getVerboseBuffer() );
//	}
//_REG_TEST_( COMP_5_2, instCOMP_5_2, mrIntStrCompFail, L( "compare different strings" ) )
//
//
////---------------------------------------------------------------------------------------
//// Test string compare.
//_DECL_TEST_( mrIntWStrComp, mr_test::testCase )
//	bool test()		
//	{ 
//		return mr_test::VerbCompareEqual( FL, std::wstring( L"Fred" ), std::wstring( L"Fred" ), this->getVerboseBuffer());
//	}
//_REG_TEST_( COMP_6_1, instCOMP_6_1, mrIntWStrComp, L( "compare same wide strings" ) )
//
//
////---------------------------------------------------------------------------------------
//// Test string compare.
//_DECL_TEST_( mrIntWStrCompFail, mr_test::testCase )
//	bool test()		
//	{ 
//		return mr_test::VerbCompareEqual( FL, std::wstring( L"Fred" ), std::wstring( L"George" ), this->getVerboseBuffer());
//	}
//_REG_TEST_( COMP_6_2, instCOMP_6_2, mrIntWStrCompFail, L( "compare differente wide strings" ) )
//
//
//
////// Test narrow and wide string compare.
////_DECL_TEST_( mrWandWStrComp, mr_test::testCase )
////	bool test()		
////	{ 
////		return mr_test::VerbCompareEqual( FL, std::wstring( L"Fred" ), std::string( "Fred" ), *this );
////	}
////_REG_TEST_( COMP_7_1, instCOMP_7_1, mrIntWStrCompFail, L( "compare same strings - wide and narrow" ) )
//
//
//
//
//
//
//
////_DECL_TEST_( CleanIniLoad, IniReaderTests )
////_REG_TEST_( INI_1, instINI_1, CleanIniLoad, L( "Load clean Ini file" ) )
//
//
////// Put some garbage before the first section
////_DECL_TEST_( PreSecGrbgIni, IniReaderTests )
////	virtual void addTopFileGarbage( mr_utils::mr_ofstream& os  )
////	{
////		this->printLine( os, L( "#Comment line" ) );
////		this->printLine( os, L( "line without comment indicator - garbage" ) );
////	}
////_REG_TEST_( INI_2, instINI_2, PreSecGrbgIni, L( "Load Ini file garbage before first section" ) )
////
////
////// Put some garbage into the middle of a section
////_DECL_TEST_( MidSecGrbgIni, IniReaderTests )
////	virtual void addMidSectionGarbage( mr_utils::mr_ofstream& os  )
////	{
////		this->printLine( os, L( "#Comment line" ) );
////		this->printLine( os, L( "line without comment indicator - garbage" ) );
////	}
////_REG_TEST_( INI_3, instINI_3, MidSecGrbgIni, L( "Load Ini file garbage mid section" ) )
////
////
////// Put some garbage into the end of a section
////_DECL_TEST_( EndSecGrbgIni, IniReaderTests )
////	virtual void addPostSectionGarbage( mr_utils::mr_ofstream& os  )
////	{
////		this->printLine( os, L( "#Comment line" ) );
////		this->printLine( os, L( "line without comment indicator - garbage" ) );
////	}
////_REG_TEST_( INI_4, instINI_4, EndSecGrbgIni, L( "Load Ini file garbage after section" ) )
////
////
////
////// Create empty section
////_DECL_TEST_( EmptySectIni, IniReaderTests )
////	virtual void addSectionForEmpty( mr_utils::mr_ofstream& os  )
////	{
////		this->printSection( os, L( "Empty Section Name" ) );
////	}
////_REG_TEST_( INI_5, instINI_5, EmptySectIni, L( "Load Ini file with empty section" ) )
////
////
