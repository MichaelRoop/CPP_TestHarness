// CppTestDevConsole.cpp : Defines the entry point for the console application.
//


// TODO - temp for win tests
#include "windows.h"

#include "CppTestEngine.h"
//#include "CppTestLogEngine.h"
#include "CppTestFileScriptReader.h"

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

class PrintCaseNames {
public:
//	PrintCaseNames() {}
	void operator () (const mr_utils::mr_string& name) {
		mr_cout << _L_("\t") << name << std::endl;
	}
};

//std::vector<mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> >
class PrintFixtureCaseNames {
public:
	void operator () (mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> fixture) {
		mr_utils::mr_pointerException::ptrAssert(fixture.getPtr(), _FL_ );
		mr_cout << fixture->FixtureName() << std::endl;
		std::for_each(
			fixture->TestCaseNames().begin(), 
			fixture->TestCaseNames().end(), PrintCaseNames());
	}
};


typedef void (__cdecl *ptrFunc)();
//typedef void (__stdcall *ptrFunc)();
//#define PROC_OFFSET 0x000112C1


static void MyLoggedEventHandler(const MrTest::ICase& testCase) {
	mr_cout << _L_(" # # # # Received a log event for test:") << testCase.FixtureName << _L_(".") << testCase.Name << _L_(" with results:") << MrTest::ICase::ToString(testCase.Status) << std::endl;
}

static void MySecondLoggedEventHandler(const MrTest::ICase& testCase) {
	mr_cout << _L_(" @ @ @ @ Received a log event for test:") << testCase.FixtureName << _L_(".") << testCase.Name << _L_(" with results:") << MrTest::ICase::ToString(testCase.Status) << std::endl;
}

static void MySummaryEventHandler(const MrTest::IRunSummary& summary) {
	mr_cout << _L_("& & & & & Summary Event") << std::endl
		<< _L_("Success = ") << summary.Total(MrTest::ICase::ST_SUCCESS) << std::endl
		<< _L_("Fixture Setup Failure = ") << summary.Total(MrTest::ICase::ST_FAIL_FIXTURE_SETUP) << std::endl
		<< _L_("Setup Failure = ") << summary.Total(MrTest::ICase::ST_FAIL_SETUP) << std::endl
		<< _L_("Test Failure = ") << summary.Total(MrTest::ICase::ST_FAIL_TEST) << std::endl
		<< _L_("Teardown Failure = ") << summary.Total(MrTest::ICase::ST_FAIL_CLEANUP) << std::endl
		<< _L_("Disabled = ") << summary.Total(MrTest::ICase::ST_DISABLED) << std::endl
		<< _L_("Not Found = ") << summary.Total(MrTest::ICase::ST_NOT_EXISTS) << std::endl
		<< _L_("Total = ") << summary.Total() << std::endl;
}


int main(int argc, char* argv[]) {

	//std::vector<std::string> namesVector;


	//std::vector< mr_utils::SharedPtr<MrTest::IFixture> > fixtures;
	//fixtures.push_back(mr_utils::SharedPtr<MrTest::IFixture>(new MrTest::Fixture(_L_("MyFixture"))));
	//mr_cout << _L_("Fixture Name:") << fixtures[0]->Name();


	//mr_utils::SharedPtr<MrTest::IFixture> fixture(new MrTest::Fixture(_L_("MyFixture")));
	//fixture = new MrTest::Fixture(_L_("MyFixture"));

	////mr_cout << _L_("Fixture Name:") << fixture->Name();

	//return 0;



//
//		//HMODULE handle = LoadLibraryEx(L"C:\\Dev\\ExperimentDll.dll", NULL, DONT_RESOLVE_DLL_REFERENCES); 
//		HMODULE handle = LoadLibraryEx(L"..\\Debug\\CppTestUtilsTestCases.dll", NULL, DONT_RESOLVE_DLL_REFERENCES); 
//		if (handle == NULL) {
//			std::cout << "library load failed" << std::endl;
//			FreeLibrary(handle);
//			return 1;
//		}
//			std::cout << "library loaded" << std::endl;
//
//
//
//		assert(((PIMAGE_DOS_HEADER)handle)->e_magic == IMAGE_DOS_SIGNATURE);
//
//		PIMAGE_NT_HEADERS header = (PIMAGE_NT_HEADERS) ((BYTE *)handle + ((PIMAGE_DOS_HEADER)handle)->e_lfanew);
//		assert(header->Signature == IMAGE_NT_SIGNATURE);
//		assert(header->OptionalHeader.NumberOfRvaAndSizes > 0);
//
//		PIMAGE_EXPORT_DIRECTORY exports = (PIMAGE_EXPORT_DIRECTORY) 
//			((BYTE *)handle + header->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
//		PVOID names = (BYTE *)handle + exports->AddressOfNames;
//
//		
//				
//		for (unsigned int i = 0; i < exports->NumberOfNames; i++) {
//			printf("Export Function Name: |%s|\n", (BYTE *)handle + ((DWORD *)names)[i]);
//			namesVector.push_back( (char*)((BYTE *)handle + ((DWORD *)names)[i]));
//		}
//		//FreeLibrary(handle);
//
//
////return 0;

//
//	std:: wcout << "Func Name:" << MAKEINTRESOURCEA(1) << std::endl;
//
//	std::cout << "Before getting function pointer:" << std::endl;

	//	ptrFunc Func = (ptrFunc) ( GetProcAddress(handle, "MyFunc") );

	////	ptrFunc Func = (ptrFunc) ( GetProcAddress(handle, "MyFunc") );
////	ptrFunc Func = (ptrFunc) ( (handle + PROC_OFFSET) );
//
//	ptrFunc Func = (ptrFunc) ( GetProcAddress(handle, MAKEINTRESOURCEA(1)) );
//
//

	/*
	std::cout << "After getting function pointer" << std::endl;
	if (Func == NULL) {
		std::cout << "Function load failed" << std::endl;
		FreeLibrary(handle);
		return 1;
	}

	std::cout << "Function load succeeded" << std::endl;


//	
	Func() ;
	std::cout << "After calling function pointer" << std::endl;
//
*/
	//	FreeLibrary(handle);
	//return 0;


	//std::for_each(namesV.begin(), namesV.end(), ExecDllFunctionFunctor(handle));


	if (checkParams( 1, argc, argv )) {
		try {
			MrTest::Engine& eng = MrTest::Engine::Instance();
			eng.LoadTests(L"..\\Debug\\CppTestUtilsTestCases.dll");

			// Print out list of loaded tests - temp test
			std::vector<mr_utils::SharedPtr<MrTest::IFixutureTestCaseNames> > testNames = eng.GetTestNames();
			std::for_each(testNames.begin(), testNames.end(), PrintFixtureCaseNames());
			
			mr_cout << _L_("Loading Configuration from ./CppTestConfig.ini") << std::endl;
			eng.GetLogEngine().LoadLoggers("CppTestConfig.ini", _L_("INI"));

			// Test register event call backs
			eng.RegisterLoggedEvent(MyLoggedEventHandler);
			eng.RegisterLoggedEvent(MySecondLoggedEventHandler);
			eng.RegisterSummaryEvent(MySummaryEventHandler);


			// The include path is provided for now until we can replace with test runner concept
			MrTest::FileScriptReader reader( argv[1] );
			reader.Open();

			MrTest::ListBuilder listBuilder;
			//listBuilder.Build(reader);

			//MrTest::ListBuilder listBuilder;
			eng.ProcessTestList(listBuilder.Build(reader));
			//eng.ProcessScript( reader );

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
