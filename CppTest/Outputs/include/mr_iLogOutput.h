///--------------------------------------------------------------------------------------
/// @file	mr_iLogOutput.h
/// @brief	Output Interface to be used with logger objects.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_ILOG_OUTPUT_H)
#define MR_ILOG_OUTPUT_H

#include "mr_string.h"


namespace mr_test
{

//----------------------------------------------------------------------------------------
/// @briefs	Pure virtual base class for outputing logging information.
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
class iLogOutput
{
public:

	/// @brief	Initialise the object.
	///
	/// @return	true if successful, otherwise false.
	virtual bool initOutput() = 0;


	/// @brief	Close the object.
	///
	/// @return	true if successful, otherwise false.
	virtual void closeOutput() = 0;


	/// @brief	Write to the output object.
	///
	/// @exception mr_utils::mr_exception if output is not open.
	///
	/// @return	true if successful, otherwise false.
	virtual bool write( const mr_utils::mr_string& str ) = 0;

};


}

#endif