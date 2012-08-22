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
#include "CppTestFileOutput.h"
#include "mr_sstream.h"
#include "mr_toStream.h"
#include "mr_exception.h"
#include "mr_defines.h"


namespace CppTest {


FileOutput::FileOutput(const std::string& filename) : ILogOutput(), m_filename(filename) {
}


bool FileOutput::InitOutput() {
	if (m_file.is_open()) {
		m_file.close();
	}

	mr_utils::mr_exception::assertCondition( !m_filename.empty(), FL, L("No file name") );
	this->m_file.open( m_filename.c_str() );

	mr_utils::mr_stringstream ss;
	mr_utils::ToStream(ss, this->m_filename) << _L_(" cannot be opened");
	mr_utils::mr_exception::assertCondition(this->m_file.is_open(), _FL_, ss.str());

	return m_file.is_open();
}


void FileOutput::CloseOutput() {
	if (this->m_file.is_open()) {
		this->m_file.close();
	}
}


bool FileOutput::Write(const mr_utils::mr_string& str) {
	if (!this->m_file.is_open()) {
		mr_utils::mr_stringstream ss;
		mr_utils::ToStream(ss, this->m_filename) << _L_(" cannot be opened");
		mr_utils::mr_exception::assertCondition(false, FL, ss.str());
		return false;
	}
	this->m_file << str.c_str() << std::endl;
	return true;
}

} // end namespace
