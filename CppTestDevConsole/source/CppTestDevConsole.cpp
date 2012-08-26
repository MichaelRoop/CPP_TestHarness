// CppTestDevConsole.cpp : Defines the entry point for the console application.
//



#include "CppTestEngine.h"
//#include "CppTestLogEngine.h"
#include "CppTestFileScriptReader.h"

#include "mr_char.h"
#include "mr_iostream.h"
#include "mr_fileException.h"
#include "CppTestScriptException.h"
//
////#include <iostream>
//
//#include "mr_SharedPtr.h"


// Test in including the Utils
#include "mr_doCompare.h"
static void CompareFunc() {
	int i = 2;
	int j = 2;
	mr_cout << _L_("DoCompare::equals(2,2):") << mr_utils::DoCompare<int,int>::equal(2, 2) << std::endl;

	mr_cout << _L_("Compare::equals(2,2):") << mr_utils::DoCompare<int,int>::equal(2, 1) << std::endl;
	mr_cout << _L_("Compare::notequals(2,2):") << mr_utils::DoCompare<int,int>::equal(3, 4) << std::endl;
}

#include "mr_exception.h"
static void ExceptionFunc() {
	mr_utils::mr_exception e("filename", 1000, _L_("My message contained in exception"));
	mr_cout << _L_("mr_exception msg:") << e.msg() << std::endl;
}

//#include "CppTestCase.h"
//static void TestCaseFunc() {
//	CppTest::Case c(_L_("My nifty test case"), _L_("test case description"));
//
//	mr_cout << _L_("Test Case Name:") << c.Name << std::endl;
//}

#include "mr_SharedPtr.h"
static void SharedPtrFunc() {
	mr_utils::SharedPtr<mr_utils::mr_exception> p(new mr_utils::mr_exception("filename", 1000, _L_("My message contained in exception")));
	mr_cout << _L_("mr_exception msg from within shared pointer:") << p->msg() << std::endl;
}

#include "mr_ini_file.h"
static void IniFileFunc() {
	mr_inireader::iniFile fx;

	mr_inireader::iniFile f(std::string("MyFileName"));
	//std::cout << _L_("mr_reader::iniFile:") << f.name() << std::endl;
}




bool checkParams( int required, int argc, char* argv[] );
void holdScreen();


int main(int argc, char* argv[]) {

	CompareFunc();
	ExceptionFunc();
	//TestCaseFunc();
	SharedPtrFunc();
	IniFileFunc();


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
		//holdScreen();
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
