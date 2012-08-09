///--------------------------------------------------------------------------------------
/// @file	mr_fileOutput.h
/// @brief	Output class to output logger information to a file.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_FILE_OUTPUT_H)
#define MR_FILE_OUTPUT_H


#include "mr_iLogOutput.h"
#include "mr_fstream.h"


namespace mr_test
{

//----------------------------------------------------------------------------------------
/// @brief	Class for outputing logging information to a file.
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
/// This class is used by derived logger classes to output the log data after formating.
///
//----------------------------------------------------------------------------------------
class fileOutput : public iLogOutput
{
public:

	/// @brief	Constructor.
	///
	/// @param	filename	Name of the output log file.
	fileOutput( const std::string& filename );


	/// @brief	Initialise the object.
	///
	/// @exception	mr_exception if the file name is empty or the file cannot be opened.
	///
	/// @return	true if successful, otherwise false.
	bool initOutput();


	/// @brief	Close the object.
	///
	/// @return	true if successful, otherwise false.
	void closeOutput();


	/// @brief	Write to the output object.
	///
	/// @exception mr_utils::mr_exception if file is not open.
	///
	/// @return	true if successful, otherwise false.
	bool write( const mr_utils::mr_string& str );

private:

	std::string				m_filename;	///< Log file name.
	mr_utils::mr_ofstream	m_file;		///< Log file object.


	/// @brief	Default constructor hidden to protect against default construction.
	fileOutput();
};



}

#endif