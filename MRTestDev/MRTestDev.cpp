// MRTestDev.cpp : Defines the entry point for the console application.
//


#include "CppTestEngine.h" // change test
#include "mr_iostream.h"
//#include "mr_consoleOutput.h"
#include "mr_exception.h"
#include "mr_fileException.h"
#include "mr_scriptException.h"
#include "mr_fileScriptReader.h"
#include "mr_defines.h"


#include "mr_logFactory.h"


#include <iostream>

#include <algorithm>
#include <functional>

bool checkParams( int required, int argc, char* argv[] );
void holdScreen();


int main(int argc, char* argv[])
{

	if (checkParams( 1, argc, argv ))
	{
		try
		{
			CppTest::Engine& eng = CppTest::Engine::Instance();
			eng.GetLogEngine().loadLoggers( "TestHarnessConfig.ini", L("INI") );

			mr_test::fileScriptReader reader( argv[1] );
			reader.Open();
			eng.ProcessScript( reader );
		} 
		catch( const mr_test::scriptException e ) {
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
}


bool checkParams( int required, int argc, char* argv[] )
{
	if (argc < required + 1)
	{
		std::cout << "You need to have the correct arguments - " << argv[0] << " testscriptname.txt" << std::endl;
		holdScreen();
		return false;
	}
	return true;
}


void holdScreen()
{
	std::cout << "Type a char and press Enter to end program" << std::endl;

	// to intercept and wait.
	//int x;
	//std::cin >> x;
}
