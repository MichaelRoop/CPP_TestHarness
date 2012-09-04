// CppTestDevConsole.cpp : Defines the entry point for the console application.
//


// TODO - temp for win tests
#include "windows.h"

#include "CppTestEngine.h"
//#include "CppTestLogEngine.h"
#include "CppTestFileScriptReader.h"
#include "MrTestCommandLineReader.h"
#include "MrTestVectorLineReader.h"

#include "mr_char.h"
#include "mr_iostream.h"
#include "mr_fileException.h"
#include "CppTestScriptException.h"
#include "CppTestListBuilder.h"
#include "ICppTestRunSummary.h"

#include "mr_pointerException.h"
#include <algorithm>

// temp
#include "CppTestFixture.h"


bool checkParams( int required, int argc, char* argv[] );
void holdScreen();

class PrintCaseNamesFunctor {
public:
	void operator () (const mr_utils::mr_string& name) {
		mr_cout << _L_("\t") << name << std::endl;
	}
};

//std::vector<mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> >
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


static void MyLoggedEventHandler(const MrTest::ICase& testCase) {
	mr_cout << _L_(" # # # # Received a log event for test:") << testCase.FixtureName << _L_(".") << testCase.Name << _L_(" with results:") << MrTest::ICase::ToString(testCase.Status) << std::endl;
}

static void MySecondLoggedEventHandler(const MrTest::ICase& testCase) {
	mr_cout << _L_(" @ @ @ @ Received a log event for test:") << testCase.FixtureName << _L_(".") << testCase.Name << _L_(" with results:") << MrTest::ICase::ToString(testCase.Status) << std::endl;
}

static void MySummaryEventHandler(const MrTest::IRunSummary& summary) {
	mr_cout << _L_("& & & & & Summary Event") << std::endl
		<< _L_("Success =            ") << summary.Total(MrTest::ICase::ST_SUCCESS) << std::endl
		<< _L_("Fixture Setup Fail = ") << summary.Total(MrTest::ICase::ST_FAIL_FIXTURE_SETUP) << std::endl
		<< _L_("Setup Fail =         ") << summary.Total(MrTest::ICase::ST_FAIL_SETUP) << std::endl
		<< _L_("Test Fail =          ") << summary.Total(MrTest::ICase::ST_FAIL_TEST) << std::endl
		<< _L_("Teardown Fail =      ") << summary.Total(MrTest::ICase::ST_FAIL_CLEANUP) << std::endl
		<< _L_("Disabled =           ") << summary.Total(MrTest::ICase::ST_DISABLED) << std::endl
		<< _L_("Not Found =          ") << summary.Total(MrTest::ICase::ST_NOT_EXISTS) << std::endl
		<< _L_("Total Tests Run =    ") << summary.Total() << std::endl;
}


int main(int argc, char* argv[]) {

	if (checkParams( 1, argc, argv )) {
		try {
			MrTest::Engine& eng = MrTest::Engine::Instance();
			eng.LoadTests(L"..\\Debug\\CppTestUtilsTestCases.dll");

			// Print out list of loaded tests - temp test
			mr_cout << L("List of Test Cases from DLL") << std::endl;
			std::vector<mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> > testNames = eng.GetTestNames();
			std::for_each(testNames.begin(), testNames.end(), PrintFixtureCaseNamesFunctor());
			
			mr_cout << _L_("Loading Configuration from ./CppTestConfig.ini") << std::endl;
			eng.LoadLoggersByFileDefinition("CppTestConfig.ini", _L_("INI"));

			// Test register event call backs
			eng.RegisterLoggedEvent(MyLoggedEventHandler);
			eng.RegisterLoggedEvent(MySecondLoggedEventHandler);
			eng.RegisterSummaryEvent(MySummaryEventHandler);


			// The include path is provided for now until we can replace with test runner concept
			//MrTest::FileScriptReader reader( argv[1] );

			//MrTest::CommandLineReader reader(L("TokenizerTests1.UTL_TOK_1_3$arg1=3434||arg2=jjf"));
			//MrTest::CommandLineReader reader(L("TokenizerTests1"));
			
			std::vector<mr_utils::mr_string> testVector;
			testVector.push_back(L("TokenizerTests1.UTL_TOK_1_1"));
			testVector.push_back(L("TokenizerTests1.UTL_TOK_1_3$arg1=3434||arg2=jjf"));
			MrTest::VectorLineReader reader(testVector);

			reader.Open();
			eng.ProcessTestList(MrTest::ListBuilder().Build(reader));
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
			mr_cout << e.what() << std::endl;
		}
		catch( ... ) {
			mr_cout << L("Unknown exception") << std::endl;
		}
		//holdScreen();
	}

	// Temp DLL load test
//	FreeLibrary(handle);


	return 0;
}

bool checkParams(int required, int argc, char* argv[]) {
	if (argc < required + 1) {
		mr_cout << "You need to have the correct arguments - " << argv[0] << " testscriptname.txt" << std::endl;
		holdScreen();
		return false;
	}
	return true;
}


void holdScreen() {
	mr_cout << "Type a char and press Enter to end program" << std::endl;
	// to intercept and wait.
	//int x;
	//std::cin >> x;
}
