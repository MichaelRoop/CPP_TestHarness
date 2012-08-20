//
//
//
//#include "mr_case.h"
//#include "mr_testMacros.h"
//#include "mr_string.h"
//#include "mr_char.h"
//#include "mr_iostream.h"
//
//
//class UtilStrTrimTests : public mr_test::testCase
//{
//public:
//
//	UtilStrTrimTests( const mr_utils::mr_string& testName, const mr_utils::mr_string& argStr ) 
//		: mr_test::testCase( testName, argStr )
//	{
//	}
//
//	bool test()
//	{
//		m_strPost = mr_utils::Trim( m_strPre );
//		return this->print();
//	}
//
//
//	bool initStr( const mr_utils::mr_string& str )
//	{
//		m_strPre = str;
//		m_strPost = str;
//		return true;
//	}
//
//	bool print()
//	{
//		mr_cout << this->name() << " - Triming results before: |" << m_strPre.c_str() << "|, post: |" << m_strPost.c_str() << "|" << std::endl;
//		return true;
//	}
//
//protected:
//
//	mr_utils::mr_string m_strPre;
//	mr_utils::mr_string m_strPost;
//
//};
//
//
//class UtilStrTrimRTests : public UtilStrTrimTests
//{
//public:
//	UtilStrTrimRTests( const mr_utils::mr_string& testName, const mr_utils::mr_string& argStr ) 
//		: UtilStrTrimTests( testName, argStr )
//	{
//	}
//
//	bool test()
//	{
//		m_strPost = mr_utils::TrimRight( m_strPre );
//		return this->print();
//	}
//};
//
//
//_DECL_TEST_( TrimRightTest1, UtilStrTrimRTests )
//	bool setup()	{ return this->initStr( L( "This is a str  \t\n\r\0" ) ); }
//_REG_TEST_ANON_( UTL_STR_RTRIM_1, instUTL_STR_RTRIM_1, TrimRightTest1 )
//
//
//_DECL_TEST_( TrimRightTest2, UtilStrTrimRTests )
//	bool setup()	{ return this->initStr( L( "" ) ); }
//_REG_TEST_ANON_( UTL_STR_RTRIM_2, instUTL_STR_RTRIM_2, TrimRightTest2 )
//
//
//class UtilStrTrimLTests : public UtilStrTrimTests
//{
//public:
//	UtilStrTrimLTests( const mr_utils::mr_string& testName, const mr_utils::mr_string& argStr ) 
//		: UtilStrTrimTests( testName, argStr )
//	{
//	}
//
//	bool test()
//	{
//		m_strPost = mr_utils::TrimLeft( m_strPre );
//		return this->print();
//	}
//};
//
//
//
//_DECL_TEST_( TrimLeftTest1, UtilStrTrimLTests )
//	bool setup()	{ return this->initStr( L( "  \t\n\rThis is a str" ) ); }
//_REG_TEST_ANON_( UTL_STR_LTRIM_1, instUTL_STR_LTRIM_1, TrimLeftTest1 )
//
//
//_DECL_TEST_( TrimLeftTest2, UtilStrTrimLTests )
//	bool setup()	{ return this->initStr( L( "" ) ); }
//_REG_TEST_ANON_( UTL_STR_LTRIM_2, instUTL_STR_LTRIM_2, TrimLeftTest2 )
//
//
//_DECL_TEST_( TrimTest1, UtilStrTrimTests )
//	bool setup()	{ return this->initStr( L( "  \t\n\r  This is a str  \t\n\r  " ) ); }
//_REG_TEST_ANON_( UTL_STR_TRIM_1, instUTL_STR_TRIM_1, TrimTest1 )
//
//
//_DECL_TEST_( TrimTest2, UtilStrTrimTests )
//	bool setup()	{ return this->initStr( L( "" ) ); }
//_REG_TEST_ANON_( UTL_STR_TRIM_2, instUTL_STR_TRIM_2, TrimTest2 )
//
//
//
