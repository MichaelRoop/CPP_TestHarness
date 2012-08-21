///--------------------------------------------------------------------------------------
/// @file	CppTestCompareFunctions.h
/// @file	mr_compareFunctions.cpp
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "CppTestCompareFunctions.h"
#include "mr_toStream.h"


namespace CppTest
{

bool WriteToMsgBuff(mr_utils::mr_stringstream& buffer, const mr_utils::mr_string& msg, bool success) {
	if (!success) {
		buffer << msg.c_str();
	}
	return success;
}


void WriteToVerboseBuffHead( const char* file, int line, mr_utils::mr_stringstream&	buffer) {
	buffer	<< L( "Comparison Failed,  " ) << L("File : " );
	mr_utils::ToStream(buffer, mr_utils::ExtractFileName(file));
	buffer	<< L(", Line : " ) 	<< line													<<std::endl
			<< L( "---------------------------------------------------------------" )	<< std::endl
			<< L( "Expected Value: " )													<< std::endl
			<< L( "----------------" )													<< std::endl;
}


void WriteToVerboseBuffMid(mr_utils::mr_stringstream& buffer) {
	buffer	<< std::endl << std::endl
			<< L( "Actual Value: " )	<< std::endl
			<< L( "-------------" )		<< std::endl;
}


} // namespace

