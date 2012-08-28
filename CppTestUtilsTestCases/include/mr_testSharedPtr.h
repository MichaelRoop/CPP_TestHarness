/////--------------------------------------------------------------------------------------
///// @file	mr_testSharedObject.cpp
///// @brief	Test case file for the SharedObject object.
/////
///// @author		Michael Roop
///// @date		2010
///// @version	1.0
/////
///// Copyright 2010 Michael Roop
/////--------------------------------------------------------------------------------------







//
//#include "mr_case.h"
//#include "mr_testMacros.h"
//#include "mr_sharedPtr.h"
//#include "mr_compareFunctions.h"
//
//
//// Test object to test SharedPtr object.  VC 2008 will not fail if you delete
//// and then access an unsigned pointer, so we will create this object to make
//// a better test.
//class SharedPtrHeldObj
//{
//public:
//	int m_val;
//};
//
//
//
//// Test for reference count on constructor.
//_DECL_TEST_( testSharedPtr1, mr_test::testCase )
//	bool test()	
//	{
//		mr_utils::SharedPtr<unsigned> sp( new unsigned() );
//		return mr_test::VerbCompareEqual( FL, (unsigned)1, sp.getCount(), this->getVerboseBuffer(), L("Mismatch on reference count") );
//	}
//_REG_TEST_( UTIL_SHARED_PTR_1, instUTIL_SHARED_PTR_1, testSharedPtr1, L( "With constructor with pointer" ) )
//
//
//// Test for reference count 2 on constructor and copy constructor.
//_DECL_TEST_( testSharedPtr2, mr_test::testCase )
//	bool test()	
//	{
//		mr_utils::SharedPtr<unsigned> sp( new unsigned() );
//		mr_utils::SharedPtr<unsigned> sp2( sp );
//		return mr_test::VerbCompareEqual( FL, (unsigned)2, sp.getCount(), this->getVerboseBuffer(), L("Mismatch on reference count") );
//	}
//_REG_TEST_( UTIL_SHARED_PTR_2, instUTIL_SHARED_PTR_2, testSharedPtr2, L( "With copy constructor creating second" ) )
//
//
//// Test reset.
//_DECL_TEST_( testSharedPtr3, mr_test::testCase )
//	bool test()	
//	{
//		mr_utils::SharedPtr<unsigned> sp( new unsigned() );
//		sp.reset();
//		return mr_test::VerbCompareEqual( FL, (unsigned)0, sp.getCount(), this->getVerboseBuffer(), L("Mismatch on reference count") );
//	}
//_REG_TEST_( UTIL_SHARED_PTR_3, instUTIL_SHARED_PTR_3, testSharedPtr3, L( "With reset called which deletes last copy" ) )
//
//
//// Test for reference count 2 on constructor and assignment operator.
//_DECL_TEST_( testSharedPtr4, mr_test::testCase )
//	bool test()	
//	{
//		mr_utils::SharedPtr<unsigned> sp( new unsigned() );
//		mr_utils::SharedPtr<unsigned> sp2 = sp;
//		return mr_test::VerbCompareEqual( FL, (unsigned)2, sp.getCount(), this->getVerboseBuffer(), L("Mismatch on reference count") );
//	}
//_REG_TEST_( UTIL_SHARED_PTR_4, instUTIL_SHARED_PTR_4, testSharedPtr4, L( "With Assignment operator" ) )
//
//
//// Test for decrement from destructor.
//_DECL_TEST_( testSharedPtr5, mr_test::testCase )
//	bool test()	
//	{
//		mr_utils::SharedPtr<unsigned> sp( new unsigned() );
//		{
//			mr_utils::SharedPtr<unsigned> sp2 = sp;
//		}
//		return mr_test::VerbCompareEqual( FL, (unsigned)1, sp.getCount(), this->getVerboseBuffer(), L("Mismatch on reference count") );
//	}
//_REG_TEST_( UTIL_SHARED_PTR_5, instUTIL_SHARED_PTR_5, testSharedPtr5, L( "decrement on destruction" ) )
//
//
//// Test with vector. Touches default constructor, assignment operator and destructor.
//_DECL_TEST_( testSharedPtr6, mr_test::testCase )
//	bool test()	
//	{
//		mr_utils::SharedPtr<unsigned> sp( new unsigned() );
//		{
//			std::vector<mr_utils::SharedPtr<unsigned> > v;
//			v.push_back( mr_utils::SharedPtr<unsigned>( sp ) );
//			v.push_back( mr_utils::SharedPtr<unsigned>( sp ) );
//			v.push_back( mr_utils::SharedPtr<unsigned>( sp ) );
//			v.push_back( mr_utils::SharedPtr<unsigned>( sp ) );
//			mr_test::VerbCompareEqual( FL, (unsigned)5, sp.getCount(), this->getVerboseBuffer(), L("Mismatch on reference count") );
//		}
//		return mr_test::VerbCompareEqual( FL, (unsigned)1, sp.getCount(), this->getVerboseBuffer(), L("Mismatch on reference count") );
//	}
//_REG_TEST_( UTIL_SHARED_PTR_6, instUTIL_SHARED_PTR_6, testSharedPtr6, L( "Used in std::vector" ) )
//
//
////// Test for deletion of initial pointer on assignment of new if count = 0.
////_DECL_TEST_( testSharedPtr7, mr_test::testCase )
////	bool test()	
////	{
////
////		SharedPtrHeldObj* val1 = new SharedPtrHeldObj();
////		mr_utils::SharedPtr<SharedPtrHeldObj> sp( val1 );
////		
////		SharedPtrHeldObj* val2 = new SharedPtrHeldObj();
////		sp = val2;
////
////		//bool ret = true;
////		//ret += mr_test::VerbCompareEqual( FL, (unsigned)1, sp.getCount(), *this, L("Mismatch on reference count") );
////
////
////		SharedPtrHeldObj val3;
////		val3.m_val = val1->m_val;
////
////		return mr_test::VerbCompareEqual( FL, (unsigned)1, sp.getCount(), *this, L("Mismatch on reference count") );
////	}
////_REG_TEST_( UTIL_SHARED_PTR_7, instUTIL_SHARED_PTR_7, testSharedPtr7, L( "deleted held pointer" ) )
//
//
//
//
//
//
//
//
