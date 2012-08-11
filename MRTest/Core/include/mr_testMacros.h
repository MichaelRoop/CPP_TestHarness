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

#include "mr_case.h"
#include "mr_testEngine.h"
#include "mr_char.h"

///--------------------------------------------------------------------------------------
///
/// @brief	Macro to create a testCase creator object.  
///
///	The object instantiates a testCase by instantiating it in its constructor 
///	and registering it with the engine.  There is a description string.
///
/// The macro then goes on to instantiate the creator object which calls the 
///	constructor and registers the created testCase.
///
/// @param	className	The unique name of the test case creator class.  This will
///						also be stringifyed to creat the string unique ID of the 
///						intantiated testCase.
/// @param	classInst	The unique instance name of the test case creator class.
/// @param	caseClass	The unique class name of the testCase.
/// @param	caseDesc	The string description of the test case.
///
///--------------------------------------------------------------------------------------
#define MAKE_CASE_DESC( className, classInst, caseClass, caseDesc )				\
																				\
class className																	\
{																				\
public:																			\
	className( mr_utils::mr_string name, mr_utils::mr_string desc )			\
	{																			\
		/* create the test case	*/												\
		mr_test::testCase* testCase = new (caseClass)( name, desc );			\
																				\
		/* register the test case with the engine singleton.*/					\
		mr_test::engine::getInstance().regCase( testCase );						\
																				\
	}																			\
};																				\
																				\
className classInst( mr_utils::mr_string( _L_((#className)) ), mr_utils::mr_string( (caseDesc) ) );	\


///--------------------------------------------------------------------------------------
///
/// @brief	Macro to create a testCase creator object.  
///
///	The object instantiates a testCase by instantiating it in its constructor 
///	and registering it with the engine.  There is no description string.
///
/// The macro then goes on to instantiate the creator object which calls the 
///	constructor and registers the created testCase.
///
/// @param	className	The unique name of the test case creator class.  This will
///						also be stringifyed to creat the string unique ID of the 
///						intantiated testCase.
/// @param	classInst	The unique instance name of the test case creator class.
/// @param	caseClass	The unique class name of the testCase.
///
///--------------------------------------------------------------------------------------
#define MAKE_CASE( className, classInst, caseClass )							\
MAKE_CASE_DESC( className, classInst, caseClass, _L_("") )						\



//-----------------------------------------------------------------------------------
//
// Helper macros to construct and register test cases.
//
//-----------------------------------------------------------------------------------


///--------------------------------------------------------------------------------------
///
/// @brief	Main macro to declare a testCase object.
///
/// Hides the creation of the class constructor.
///
/// @param	derivedClass	The derived class name. This name is then passed to the 
///							declaration end and registration macro.
/// @param	parentClass		The parent of this testCase object.
///
///--------------------------------------------------------------------------------------
#define _DECL_TEST_( derivedClass, parentClass )									\
																					\
class derivedClass : public parentClass												\
{																					\
public:																				\
																					\
	derivedClass( const mr_utils::mr_string& testName, mr_utils::mr_string& argStr )\
		: parentClass( testName, argStr )											\
	{																				\
	}																				\


///--------------------------------------------------------------------------------------
///
/// @brief	Ends the testCase definition and calls the test case creator macro to 
///			register an instance to the engine.
///
/// example:
///
///	_DECL_TEST_( mrIntEqComp, mr_test::testCase )								\n
///		bool test()																\n
///		{																		\n
///			return mr_test::VerbCompareEqual( FL, 100, 100, *this );			\n
///		}																		\n
///	_REG_TEST_( COMP_1_1, instCOMP_1_1, mrIntEqComp, L( "compare same ints" ) )	\n
//
/// @param	className		The class name to be created.  Used as the unique identifier
///							creator class and stingifyed to be used as ID of the test case.
/// @param	classInst		The instance name of the creator class.
/// @param	derivedClass	The derived testCase name. This is the same name as was 
///							passed in as the derivedClass argument of the DECL_CASE_CLASS
///							macro.
///	@param	caseDesc		An mr_utils::me_string with the test description.
///
///
///--------------------------------------------------------------------------------------
#define _REG_TEST_( className, classInst, derivedClass, caseDesc )		\
};																		\
MAKE_CASE_DESC( className, classInst, derivedClass, caseDesc )			\


///--------------------------------------------------------------------------------------
///
/// @brief	Ends the testCase definition and calls the test case creator macro to 
///			register an instance to the engine.  No description string is necessary.
///
/// example:
///
///	_DECL_TEST_( mrIntEqComp, mr_test::testCase )								\n
///		bool test()																\n
///		{																		\n
///			return mr_test::VerbCompareEqual( FL, 100, 100, *this );			\n
///		}																		\n
///	_REG_TEST_ANON_( COMP_1_1, instCOMP_1_1, mrIntEqComp, L( "compare same ints" ) )	\n
//
/// @param	className		The class name to be created.  Used as the unique identifier
///							creator class and stingifyed to be used as ID of the test case.
/// @param	classInst		The instance name of the creator class.
/// @param	derivedClass	The derived testCase name. This is the same name as was 
///							passed in as the derivedClass argument of the DECL_CASE_CLASS
///							macro.
///
///--------------------------------------------------------------------------------------
#define _REG_TEST_ANON_( className, classInst, derivedClass )		\
_REG_TEST_( className, classInst, derivedClass, _L_("") )				\



// Simplified macros for next generation

// Adding the test fixture to the engine
#define _ADD_TEST_FIXTURE_( _testCaseClass_ )	\
mr_test::engine::getInstance().regCase( _testCaseClass_ );						\

// Create the fixture instance with a unique variable name. This will trigger the constructor which registers it with the engine
// You can only register a fixture class once
#define _REGISTER_FIXTURE_( _fixture_ )	\
_fixture_*  ##_fixture_##Instance  = new _fixture_();  \


#define _FIXTURE_SETUP_( _fixture_,  _setup_ )		\
_fixture_->RegisterFixtureSetup(static_cast<testCase::testCase_ptr>( _setup_  ));			\


#define _FIXTURE_TEARDOWN_( _fixture_,  _teardown_ )		\
_fixture_->RegisterFixtureTeardown(static_cast<testCase::testCase_ptr>( _teardown_  ));			\


#define _TEST_SETUP_( _fixture_,  _setup_ )		\
_fixture_->RegisterTestSetup(static_cast<testCase::testCase_ptr>( _setup_  ));			\


#define _TEST_TEARDOWN_( _fixture_,  _teardown_ )		\
_fixture_->RegisterTestTeardown(static_cast<testCase::testCase_ptr>( _teardown_  ));			\


#define _REGISTER_TEST_( _fixture_, _test_, _desc_ )												\
_fixture_->RegisterTest(static_cast<testCase::testCase_ptr>( _test_ ), _L_((#_test_)), ( _desc_ ) );			\

//void RegisterTest(testCase_ptr test, const mr_utils::mr_string& name, const mr_utils::mr_string& description);

#endif