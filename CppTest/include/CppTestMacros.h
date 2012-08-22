///--------------------------------------------------------------------------------------
/// @file	mr_testMacros.h
/// @brief	Macros useful for creating small footprint test cases.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TEST_MACROS_H)
#define MR_TEST_MACROS_H

#include "CppTestFixture.h"
#include "CppTestAsserts.h"
#include "CppTestEngine.h"
#include "mr_char.h"
#include "mr_defines.h"


// Adding the test fixture to the engine
#define _ADD_TEST_FIXTURE_( _fixtureClass_ )				\
CppTest::Engine::Instance().RegisterCase( _fixtureClass_ );	\


// Create the fixture instance with a unique variable name. This will trigger the constructor which registers it with the engine
// You can only register a fixture class once
#define _REGISTER_FIXTURE_( _fixture_ )						\
_fixture_*  ##_fixture_##Instance  = new _fixture_();		\


// Register the class void method as the fixture setup method
#define _FIXTURE_SETUP_( _fixture_,  _setup_ )		\
	_fixture_->RegisterFixtureSetup(static_cast<CppTest::Fixture::fixture_method_ptr>( _setup_  ));			\


// Register the class void method as the fixture teardown method
#define _FIXTURE_TEARDOWN_( _fixture_,  _teardown_ )		\
_fixture_->RegisterFixtureTeardown(static_cast<CppTest::Fixture::fixture_method_ptr>( _teardown_  ));			\


// Register the class void method as the test setup method
#define _TEST_SETUP_( _fixture_,  _setup_ )		\
_fixture_->RegisterTestSetup(static_cast<CppTest::Fixture::fixture_method_ptr>( _setup_  ));			\


// Register the class void method as the test teardown method
#define _TEST_TEARDOWN_( _fixture_,  _teardown_ )		\
_fixture_->RegisterTestTeardown(static_cast<CppTest::Fixture::fixture_method_ptr>( _teardown_  ));			\


// Register the class void method as the test method
#define _REGISTER_TEST_( _fixture_, _test_, _desc_ )												\
_fixture_->RegisterTest(static_cast<CppTest::Fixture::fixture_method_ptr>( _test_ ), _L_((#_test_)), _L_((_desc_)) );			\


//----------------------------------------------------------------------------------
// comparison assert macros
//----------------------------------------------------------------------------------


#define _ARE_EQUAL(_fixture_,_expected_, _actual_) \
CppTest::AreEqual(_FL_, (_expected_), (_actual_), (_fixture_)->CurrentTestCase().MsgBuffer);


#define _ARE_NOT_EQUAL(_fixture_,_notexpected_, _actual_) \
CppTest::AreNotEqual(_FL_, (_notexpected_), (_actual_), (_fixture_)->CurrentTestCase().MsgBuffer);

#define _IS_TRUE_(_fixture_,_condition_,_msg_)	\
CppTest::IsTrue(_FL_, (_condition_), (_fixture_)->CurrentTestCase().MsgBuffer, (_msg_));

#define _IS_FALSE_(_fixture_,_condition_,_msg_)	\
CppTest::IsFalse(_FL_, (_condition_), (_fixture_)->CurrentTestCase().MsgBuffer, (_msg_));


//void IsTrue(
//	const char* file, int line, bool condition, mr_utils::mr_stringstream& buffer, const mr_utils::mr_string& msg) {



/*
#define _DOES_THROW(_fixture_, _exception_, _logic_) \
	try {									\
		(_logic_);							\
		_ARE_EQUAL(_fixture_, 1, 2);		\
	}										\
	catch (const (_exception_)& e) {			\
		prinf("caught exception");			\
	}										\
*/


#endif