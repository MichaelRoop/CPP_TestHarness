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

#include "ICppTestFixture.h"
#include "CppTestAsserts.h"
#include "CppTestEngine.h"
#include "mr_char.h"
#include "mr_sstream.h"
#include "mr_defines.h"


// Adding the test fixture to the engine
#define ADD_TEST_FIXTURE( _fixtureClass_ )					\
MrTest::Engine::Instance().RegisterCase( _fixtureClass_ );	\


// Create the fixture instance with a unique variable name. This will trigger the constructor which registers it 
// with the engine. You can only register a fixture class once. Place this in the dllMain for those OS which do
// not have DLL header parsing implemented
#define REGISTER_FIXTURE_MAIN( _fixture_ )						\
	_fixture_*  ##_fixture_##Instance  = new _fixture_(_L_((#_fixture_)));		\

// Dynamic loading of the fixture via a called export function. In windows the functions are discovered by parsing
// the DLL header to extract export function names which are then called. This allows the macro to be placed in 
// closer proximity to the test fixture instead of in the dllMain.  This should also be doable for linux and other
// NIX which use the ELF shared object headers.
//
// Note that we assume __cplusplus is defined. We cannot use pre processor directives in a macro. 
#if defined(WIN32)
#	define REGISTER_FIXTURE( _fixture_ )													\
	extern "C" {																			\
		__declspec(dllexport) void __cdecl ##_fixture_##_this_is_a_CppTest_loader_() {		\
			_fixture_*  ##_fixture_##instance = new _fixture_(_L_((#_fixture_)));			\
		}																					\
	}																						
#else
#	define REGISTER_FIXTURE( _fixture_ )
#endif



// Register the class void method as the fixture setup method
#define FIXTURE_SETUP( _fixture_,  _setup_ )		\
	_fixture_->RegisterFixtureSetup(static_cast<MrTest::IFixture::Ifixture_method_ptr>( _setup_  ));			\


// Register the class void method as the fixture teardown method
#define FIXTURE_TEARDOWN( _fixture_,  _teardown_ )		\
_fixture_->RegisterFixtureTeardown(static_cast<MrTest::IFixture::Ifixture_method_ptr>( _teardown_  ));			\


// Register the class void method as the test setup method
#define TEST_SETUP( _fixture_,  _setup_ )		\
_fixture_->RegisterTestSetup(static_cast<MrTest::IFixture::Ifixture_method_ptr>( _setup_  ));			\


// Register the class void method as the test teardown method
#define TEST_TEARDOWN( _fixture_,  _teardown_ )		\
_fixture_->RegisterTestTeardown(static_cast<MrTest::IFixture::Ifixture_method_ptr>( _teardown_  ));			\


// Register the class void method as the test method
#define REGISTER_TEST( _fixture_, _test_, _desc_ )												\
_fixture_->RegisterTest(static_cast<MrTest::IFixture::Ifixture_method_ptr>( _test_ ), _L_((#_test_)), _L_((_desc_)) );			\


//----------------------------------------------------------------------------------
// comparison assert macros
//----------------------------------------------------------------------------------


#define TEST_EQUAL(_fixture_,_expected_, _actual_) \
MrTest::AreEqual(_FL_, (_expected_), (_actual_), (_fixture_)->CurrentTestCase().MsgBuffer, (_fixture_)->CurrentTestCase().EmbeddedMsgBuffer);


#define TEST_NOT_EQUAL(_fixture_,_notexpected_, _actual_) \
MrTest::AreNotEqual(_FL_, (_notexpected_), (_actual_), (_fixture_)->CurrentTestCase().MsgBuffer, (_fixture_)->CurrentTestCase().EmbeddedMsgBuffer);


#define TEST_EQUAL_EX(_fixture_,_expected_, _actual_,_userMsg_)								\
(_fixture_)->CurrentTestCase().EmbeddedMsgBuffer << _userMsg_;								\
TEST_EQUAL(_fixture_,_notexpected_, _actual_,_userMsg_)


#define TEST_NOT_EQUAL_EX(_fixture_,_notexpected_, _actual_,_userMsg_)						\
(_fixture_)->CurrentTestCase().EmbeddedMsgBuffer << _userMsg_;								\
TEST_NOT_EQUAL(_fixture_,_notexpected_, _actual_)


#define TEST_TRUE(_fixture_,_condition_,_msg_)												\
(_fixture_)->CurrentTestCase().EmbeddedMsgBuffer << _msg_;									\
MrTest::IsTrue(_FL_, (_condition_), (_fixture_)->CurrentTestCase().MsgBuffer, (_fixture_)->CurrentTestCase().EmbeddedMsgBuffer);


#define TEST_FALSE(_fixture_,_condition_,_msg_)	\
(_fixture_)->CurrentTestCase().EmbeddedMsgBuffer << _msg_;									\
MrTest::IsFalse(_FL_, (_condition_), (_fixture_)->CurrentTestCase().MsgBuffer, (_fixture_)->CurrentTestCase().EmbeddedMsgBuffer);


#define TEST_FAIL(_fixture_,_msg_)																				\
(_fixture_)->CurrentTestCase().EmbeddedMsgBuffer << _msg_;														\
MrTest::Fail(_FL_, (_fixture_)->CurrentTestCase().MsgBuffer, (_fixture_)->CurrentTestCase().EmbeddedMsgBuffer);	\


//CPPTESCASE_API void Fail(
//	const char* file, int line, mr_utils::mr_stringstream& buffer, const mr_utils::mr_stringstream& userMsg);




#define TEST_THROWS(_fixture_, _logic_)																					\
do {																													\
	try {																												\
		{																												\
			_logic_																										\
		}																												\
	}																													\
	catch (std::exception&) {																							\
		break;																											\
	}																													\
	catch (...)	{																										\
		break;																											\
	}																													\
	MrTest::FailOnNotThrow(																								\
		_FL_, (_fixture_)->CurrentTestCase().MsgBuffer, (_fixture_)->CurrentTestCase().EmbeddedMsgBuffer);				\
} while(false);																											\



#define TEST_NOT_THROWS(_fixture_, _logic_)																			\
	try {																											\
		{																											\
			_logic_																									\
		}																											\
	}																												\
	catch (mr_utils::mr_exception& e) {																				\
		MrTest::FailOnThrow(																						\
			_FL_, (_fixture_)->CurrentTestCase().MsgBuffer, e, (_fixture_)->CurrentTestCase().EmbeddedMsgBuffer);	\
	}																												\
	catch (const mr_utils::mr_exception& e) {																		\
		MrTest::FailOnThrow(																						\
			_FL_, (_fixture_)->CurrentTestCase().MsgBuffer, e, (_fixture_)->CurrentTestCase().EmbeddedMsgBuffer);	\
	}																												\
	catch (std::exception& e) {																						\
		MrTest::FailOnThrow(																						\
			_FL_, (_fixture_)->CurrentTestCase().MsgBuffer, e, (_fixture_)->CurrentTestCase().EmbeddedMsgBuffer);	\
	}																												\
	catch (const std::exception& e) {																				\
		MrTest::FailOnThrow(																						\
			_FL_, (_fixture_)->CurrentTestCase().MsgBuffer, e, (_fixture_)->CurrentTestCase().EmbeddedMsgBuffer);	\
	}																												\
	catch (...)	{																									\
	}																												\


#endif
