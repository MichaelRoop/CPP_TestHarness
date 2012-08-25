///--------------------------------------------------------------------------------------
/// @file	mr_fileException.h
/// @brief	cross platform and char width file exception.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_FILE_EXCEPTIONS_H)
#define MR_FILE_EXCEPTIONS_H

#include "CrossPlatform.h"
//#include "mr_exception.h"

#include "mr_exception.h"

namespace mr_utils
{

///--------------------------------------------------------------------------------------
///
///	@brief	Class to throw exceptions which include file name.
///
/// Extendends the mr_utils::mr_exception by storing the file name and the 
/// This information is appended onto the formatted long message. The file name is 
/// converted to wide if needed.
///
/// Use the FL macro to insert the file name and line from the system.
/// Use the L() macro to provide cross char width portability.
/// Use the cross char width streaming so that the message can be displayed on both
/// both narrow and wide char compilation mode.
///
/// Example: 
///		throw mr_utils::fileException( FL, L("The file does not exist"), filename );
///
/// On the catch you can either access the different parts of the message or use the formatted
/// message.
///
///		catch( const mr_utils::mr_exception e )
///		{
///			mr_cout << e.longMsg() << std::endl;
///		}
///
///--------------------------------------------------------------------------------------
class CPPTESTUTILS_API fileException : public mr_utils::mr_exception
{
public:

	/// @brief	Constructor.
	///
	/// @param	file		The source code file where problem originates.
	/// @param	line		The source code line where problem originates.
	/// @param	msg			The message explaining the exception.
	/// @param	fileName	The name of the file the exception is thrown for.
	fileException( 
		const char*					file, 
		int							line, 
		const mr_utils::mr_string&	msg,
		const std::string&			fileName
	);


	/// @brief	Destructor.
	virtual ~fileException() throw();


	/// @brief	Returns a formated verbose exception message.
	///
	/// The format is as following.
	///    	"Exception:SourceFile:SourceLine message : ScriptFile.txt : line contents"
	///
	/// @return	Verbose exception message.
	virtual const mr_utils::mr_string longMsg() const;

protected:

	std::string			m_fileName;	///< file being tested for exception.

};



}

#endif