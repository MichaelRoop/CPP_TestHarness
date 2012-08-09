///--------------------------------------------------------------------------------------
/// @file	mr_case.h
/// @file	mr_compareFunctions.cpp
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_compareFunctions.h"
#include "mr_case.h"
#include "mr_toStream.h"


namespace mr_test
{

bool WriteToMsgBuff( mr_test::testCase& theCase, const mr_utils::mr_string& msg, bool success )
{
	if (!success)
	{
		theCase.getMsgBuffer() << msg.c_str();
	}
	return success;
}


void WriteToVerboseBuffHead( const char* file, int line, mr_test::testCase&	theCase )
{
	mr_utils::mr_ostream& os = theCase.getVerboseBuffer();
	os	<< L( "Comparison Failed,  " ) << L("File : " );
		mr_utils::ToStream( os, mr_utils::ExtractFileName( file ) );
	os	<< L(", Line : " ) 	<< line													<<std::endl
		<< L( "---------------------------------------------------------------" )	<< std::endl
		<< L( "Expected Value: " )													<< std::endl
		<< L( "----------------" )													<< std::endl;
}


void WriteToVerboseBuffMid( mr_test::testCase& theCase )
{
	theCase.getVerboseBuffer()		<< std::endl << std::endl
		<< L( "Actual Value: " )	<< std::endl
		<< L( "-------------" )		<< std::endl;
}


}

