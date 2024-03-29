///--------------------------------------------------------------------------------------
/// @file	CppTestDevConsole.cpp
/// @brief	The Console Test Runner
///
/// @author		Michael Roop
/// @date		2012
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "MrTestEngine.h"
#include "MrTestParamParser.h"
#include "MrTestScriptException.h"
#include "MrTestListBuilderFactory.h"
#include "MrTestAssertException.h"
#include "mr_fileException.h"
#include "mr_iostream.h"


/// @brief	Prevent the screen from exiting
void holdScreen();


/// @brief Event handler to push log data for individual test cases to console
static void MyLoggedEventHandler(const MrTest::ICase& testCase);


/// @brief Event handler to push test summary information to console
static void MySummaryEventHandler(const MrTest::IRunSummary& summary);


// Early research into transforming signals to exceptions
//#if defined(__linux) || defined(_linux_)
//#include <signal.h>
//#include <ucontext.h>
//static void catchSig(int num) {
//    mr_cout << L(" ### Caught signal:") << num << std::endl;
//    //throw MrTest::AssertException(_FL_, L("Caught a signal"));
////    int x =3;
////    throw x;
//}

//#endif




int main(int argc, char* argv[]) {



// Early research into transforming signals to exceptions
//#if defined(__linux) || defined(_linux_)
//    signal(SIGINT, catchSig);
//    signal(SIGSEGV, catchSig);

//#endif



	try {


//        int* x = NULL;
//        *x = 1;


		MrTest::ParamParser argParser;
		argParser.Parse(argc, argv);

		MrTest::Engine& eng = MrTest::Engine::Instance();
		eng.LoadTests(argParser.GetArg(MrTest::ParamParser::TEST_CASE_DLL));
		eng.RegisterLoggedEvent(MyLoggedEventHandler);
		eng.RegisterSummaryEvent(MySummaryEventHandler);

        std::vector<mr_utils::SharedPtr<MrTest::ITestFixtureInfoObject> > tests;

		if (argParser.HasArg(MrTest::ParamParser::TEST_CASE_LINE)) {
            tests = MrTest::ListBuilderFactory::FromLine(
                        argParser.GetArg(MrTest::ParamParser::TEST_CASE_LINE));
		}
		else if (argParser.HasArg(MrTest::ParamParser::TEST_CASE_LIST)) {
            tests = MrTest::ListBuilderFactory::FromFile(
                    argParser.GetArg(MrTest::ParamParser::TEST_CASE_LIST));
        }

        eng.ProcessTestList(tests);
		eng.UnloadTests();
	} 
	catch( const MrTest::ScriptException e ) {
		mr_cout << e.longMsg() << std::endl;
	}
	catch( const mr_utils::fileException e ) {
		mr_cout << e.longMsg() << std::endl;
	}
	catch( const mr_utils::mr_exception e ) {
		mr_cout << e.longMsg() << std::endl; 
	}
	catch( const std::exception e ) {
        if (e.what() != 0) {
            mr_cout << e.what() << std::endl;
        }
        else {
            mr_cout << L("std::exception with no information") << std::endl;
        }
	}
	catch( ... ) {
		mr_cout << L("Unknown exception") << std::endl;
	}

	//holdScreen();
	return 0;
}


void holdScreen() {
	mr_cout << "Type a char and press Enter to end program" << std::endl;
	// to intercept and wait.
	//int x;
	//std::cin >> x;
}


static void MySummaryEventHandler(const MrTest::IRunSummary& summary) {
	mr_cout 
		<< std::endl 
		<< _L_("Test Summary") << std::endl
		<< _L_("---------------------------------") << std::endl
		<< _L_("Success            = ") << summary.Total(MrTest::ICase::ST_SUCCESS) << std::endl
		<< _L_("Fail Fixture Setup = ") << summary.Total(MrTest::ICase::ST_FAIL_FIXTURE_SETUP) << std::endl
		<< _L_("Fail Setup         = ") << summary.Total(MrTest::ICase::ST_FAIL_SETUP) << std::endl
		<< _L_("Fail Test          = ") << summary.Total(MrTest::ICase::ST_FAIL_TEST) << std::endl
		<< _L_("Fail Teardown      = ") << summary.Total(MrTest::ICase::ST_FAIL_CLEANUP) << std::endl
		<< _L_("Disabled           = ") << summary.Total(MrTest::ICase::ST_DISABLED) << std::endl
		<< _L_("Not Found          = ") << summary.Total(MrTest::ICase::ST_NOT_EXISTS) << std::endl
		<< _L_("---------------------------------") << std::endl
		<< _L_("   Total Tests Run = ") << summary.Total() << std::endl << std::endl;
}


static mr_utils::mr_string currentFixtureName;


static void MyLoggedEventHandler(const MrTest::ICase& testCase) {
	if (testCase.FixtureName != currentFixtureName) {
		mr_cout << testCase.FixtureName << std::endl;
		currentFixtureName = testCase.FixtureName;
	}
	mr_cout << _L_("\t") << testCase.Name << _L_("\t") 
		<< MrTest::ICase::ToString(testCase.Status) << _L_("\t")
		<< testCase.Description << _L_("\t")
		<< testCase.SetupTime << _L_(",")
		<< testCase.ExecTime << _L_(",")
		<< testCase.CleanupTime << _L_(",")
		<< testCase.MsgBuffer.str() << _L_(",")
		<< testCase.VerboseBuffer.str() << std::endl;
}



#ifdef OLDGARBAGE_PUSH_TO_PROCESS

class PrintCaseNamesFunctor {
public:
	void operator () (const mr_utils::mr_string& name) {
		mr_cout << _L_("\t") << name << std::endl;
	}
};

class PrintFixtureCaseNamesFunctor {
public:
	void operator () (mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> fixture) {
		mr_utils::mr_pointerException::ptrAssert(fixture.getPtr(), _FL_ );
		mr_cout << fixture->FixtureName() << std::endl;
		std::for_each(
			fixture->TestCaseNames().begin(), 
			fixture->TestCaseNames().end(), PrintCaseNamesFunctor());
	}
};

	//std::vector< mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> > tcNames;
	//mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> tkn (new MrTest::FixutureTestCaseNames(L("TokenizerTests1")));
	//tkn->AddTestCaseName(L("TokenizerTests1.UTL_TOK_1_1"));
	//tkn->AddTestCaseName(L("TokenizerTests1.UTL_TOK_1_2"));
	//tcNames.push_back(tkn);
	//mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> trm(new MrTest::FixutureTestCaseNames(L("UtilStrTrimTests")));
	//tcNames.push_back(trm);


	//// Test to make sure they work and are sorted
	//std::vector<mr_utils::mr_string> testVector;
	//testVector.push_back(L("TokenizerTests1.UTL_TOK_1_3$arg1=3434||arg2=jjf"));
	//testVector.push_back(L("UtilStrTrimTests"));
	//testVector.push_back(L("TokenizerTests1.UTL_TOK_1_1"));
	//eng.ProcessTestList(MrTest::ListBuilderFactory::FromLines(testVector));
#endif
