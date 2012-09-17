///--------------------------------------------------------------------------------------
/// @file	mr_exception.h
/// @brief	A common cross platform and char width base for exceptions.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR__EXCEPTION_H)
#define MR__EXCEPTION_H

#include "mr_string.h"
#include <exception>


namespace mr_utils
{

///--------------------------------------------------------------------------------------
///
///	@brief	Pure virtual base class for exceptions
///
/// Provides source code name and line and a user defined message.
///
/// Use the FL macro to insert the file name and line from the system.
/// Use the L() macro to provide cross char width portability.
/// Use the cross char width streaming so that the message can be displayed on both
/// both narrow and wide char compilation mode.
///
/// Example: throw mr_utils::mr_exception( FL, L("The value is outside range") );
///
/// On the catch you can either access the different parts of the message or use the formatted
/// message.
///
///		catch( const mr_utils::mr_exception& e )	\n
///		{											\n
///			mr_cout << e.longMsg() << std::endl;	\n
///		}											\n
///
///--------------------------------------------------------------------------------------
class CPPTESTUTILS_API mr_exception : public std::exception
{
public:

	/// @brief	Constructor.
	///
	/// @param	file	The source code file where problem originates.
	/// @param	line	The source code line where problem originates.
	/// @param	msg		The message explaining the exception.
	mr_exception( const char* file, int line, const mr_string& msg );


	/// @brief	Destructor.
	virtual ~mr_exception() throw();


	/// @brief	Returns the exception message.
	///
	/// @return	User defined exception message.
	const mr_string& msg() const;


	/// @brief	Returns the source code file name where the problem originates.
	///
	/// @return	Source file name where problem originates.
	const mr_string fileName() const;


	/// @brief	Returns the source code file line where the problem originates.
	///
	/// @return	Source file line where problem originates.
	int fileLine() const;

	
	/// @brief	Returns a formated verbose exception message.
	///
	/// The format is as following.  \n
	///    	"Exception:SourceFileName:SourceFileLine Exception message"
	///
	/// @return	Verbose exception message.
	virtual const mr_utils::mr_string longMsg() const;



	/// @brief	Wrapper to clean up checking for exception throw on condition.
	///
	///	@throw	Throws a mr_exception on failure
	///
	/// @param	condition		The condition to test. If false, the exception is thrown.
	/// @param	file			The source code file where problem originates.
	/// @param	line			The source code line where problem originates.
	/// @param	msg				The message explaining the exception.
	static void assertCondition( 
		bool				condition,
		const char*			file, 
		int					line, 
		const mr_string&	msg
	);




protected:

	std::string	m_fileName;	///< Source code file name.
	int			m_line;		///< Source code file line.
	mr_string	m_msg;		///< User defined exception message.


public:

	mr_exception() {}
};

}

#include <vector>
EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator<mr_utils::mr_exception>;
EXP_TEMPLATE template class CPPTESTUTILS_API std::vector<mr_utils::mr_exception>;

#endif