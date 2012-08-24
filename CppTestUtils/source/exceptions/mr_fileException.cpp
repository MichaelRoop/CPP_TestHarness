///--------------------------------------------------------------------------------------
/// @file	mr_fileException.cpp
/// @brief	cross platform and char width file exception.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_fileException.h"
#include "mr_sstream.h"
#include "mr_toStream.h"


namespace mr_utils
{

fileException::fileException( 
	const char*					file, 
	int							line, 
	const mr_utils::mr_string&	msg,
	const std::string&			fileName
)
:	mr_utils::mr_exception( file, line, msg ),
	m_fileName( fileName )
{
}


fileException::~fileException() throw()
{
}


const mr_utils::mr_string fileException::longMsg() const
{
	mr_utils::mr_stringstream ss;
	ss << mr_utils::mr_exception::longMsg() << L(" : ") << mr_utils::ToStream( ss, m_fileName );
	return ss.str();
}



} // end namespace mr_test