///--------------------------------------------------------------------------------------
/// @file	mr_consoleOutput.h
/// @brief	Output class to output logger information to the console.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_CONSOLE_OUTPUT_H)
#define MR_CONSOLE_OUTPUT_H


#include "mr_iLogOutput.h"


namespace mr_test
{

//----------------------------------------------------------------------------------------
/// @brief	Class for outputing logging information to the console.
///
/// Always use the cross character width objects and macros to make the data portable
/// for wide and narrow char compilation.
///
/// When feeding chars to the output stream use the L() macro
///	 example: fileOutput->getOsStream() << L("This is a message");
/// 
/// When feeding string objects to the output stream use the mr_string or mr_stringstream.
///	 example: 
///		mr_string s( L("This is a message") );
///		fileOutput->getOsStream() << s;
///
///
/// This class is used by derived logger classes to output the log data after formating.
///
//----------------------------------------------------------------------------------------
class consoleOutput : public iLogOutput
{
public:

	/// @brief	Initialise the object.
	///
	/// @return	true if successful, otherwise false.
	bool initOutput();


	/// @brief	Close the object.
	///
	/// @return	true if successful, otherwise false.
	void closeOutput();


	/// @brief	Write to the output object.
	///
	/// @return	true if successful, otherwise false.
	bool write( const mr_utils::mr_string& str );

};

}

#endif