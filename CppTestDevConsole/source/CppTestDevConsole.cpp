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

#include "mr_pointerException.h"
#include <algorithm>





bool checkParams( int required, int argc, char* argv[] );
void holdScreen();

class PrintCaseNames {
public:
//	PrintCaseNames() {}
	void operator () (const mr_utils::mr_string& name) {
		mr_cout << _L_("\t") << name << std::endl;
	}
};

//std::vector<mr_utils::SharedPtr<CppTest::IFixutureTestCaseNames> >
class PrintFixtureCaseNames {
public:
	void operator () (mr_utils::SharedPtr<CppTest::IFixutureTestCaseNames> fixture) {
		mr_utils::mr_pointerException::ptrAssert(fixture.getPtr(), _FL_ );
		mr_cout << fixture->FixtureName() << std::endl;
		std::for_each(
			fixture->TestCaseNames().begin(), 
			fixture->TestCaseNames().end(), PrintCaseNames());
	}
};


typedef void (__cdecl *ptrFunc)();


int main(int argc, char* argv[]) {


	//std::cout << "Before load library" << std::endl;
	//HINSTANCE handle = LoadLibrary(L"..\\Debug\\CppTestUtils.dll") ;


	//std::cout << "After load library" << std::endl;
	//if (handle == NULL) {
	//	std::cout << "library load failed" << std::endl;
	//	return 1;
	//}
	//
	//std::cout << "Before getting function pointer:" << std::endl;
	//ptrFunc Func = (ptrFunc) ( GetProcAddress(handle, "MyFunc") );
	//std::cout << "After getting function pointer" << std::endl;
	//if (Func == NULL) {
	//	std::cout << "Function load failed" << std::endl;
	//	FreeLibrary(handle);
	//	return 1;
	//}
	//
	//Func() ;
	//std::cout << "After calling function pointer" << std::endl;





	//std::for_each(namesV.begin(), namesV.end(), ExecDllFunctionFunctor(handle));


	if (checkParams( 1, argc, argv )) {
		try {
			mr_cout << _L_("Loading Configuration from ./CppTestConfig.ini") << std::endl;
			CppTest::Engine& eng = CppTest::Engine::Instance();

			// Print out list of loaded tests
			std::vector<mr_utils::SharedPtr<CppTest::IFixutureTestCaseNames> > testNames = eng.GetTestNames();
			std::for_each(testNames.begin(), testNames.end(), PrintFixtureCaseNames());


			eng.GetLogEngine().LoadLoggers("CppTestConfig.ini", _L_("INI"));

			// The include path is provided for now until we can replace with test runner concept
			CppTest::FileScriptReader reader( argv[1] );
			reader.Open();
			eng.ProcessScript( reader );
		} 
		catch( const CppTest::ScriptException e ) {
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
