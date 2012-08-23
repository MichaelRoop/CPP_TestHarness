// CppTestDevConsole.cpp : Defines the entry point for the console application.
//

#include "CppTestEngine.h"
#include "CppTestLogEngine.h"
#include "CppTestFileScriptReader.h"

#include "mr_iostream.h"
#include "mr_fileException.h"
#include "CppTestScriptException.h"

//#include <iostream>



bool checkParams( int required, int argc, char* argv[] );
void holdScreen();


int main(int argc, char* argv[]) {

	if (checkParams( 1, argc, argv )) {
		try {
			mr_cout << _L_("Loading Configuration from ./CppTestConfig.ini") << std::endl;
			CppTest::Engine& eng = CppTest::Engine::Instance();
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
		holdScreen();
	}
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
