///--------------------------------------------------------------------------------------
/// @file	MrTestIniLogInitialiser.cpp
/// @brief	Abstracts the retrieval of the intialisation data for the log object from ini
///			file.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "MrTestIniLogInitialiser.h"
#include "mr_exception.h"
#include "mr_defines.h"
#include "mr_sstream.h"
#include <algorithm>


namespace MrTest {

/// @brief	Functor to populate field vector from ini.
struct PopulateFieldListFromIni {
	PopulateFieldListFromIni(FieldVector& fields) : m_fields(fields) {
	}

	void operator () (const mr_inireader::node& theNode) {
		if (theNode.isDataNode()) {
			this->m_fields.push_back(MrTest::FieldPair(theNode.name(), theNode.value()));
		}
	}
private:
	FieldVector& m_fields;	///< receiving vector of fields.
};


/// @brief	Functor to populate field vector from ini.
struct PopulateLogList {
	PopulateLogList(std::vector<mr_utils::mr_string>& logs) : m_logs( logs ) {
	}

	void operator () (const mr_inireader::node& theNode) {
		if (theNode.isDataNode()) {
			this->m_logs.push_back( theNode.value() );
		}
	}
private:
	std::vector<mr_utils::mr_string>& m_logs;	///< receiving vector of log names.

};
//----------------- End Functors -----------------------------------


IniLogInitialiser::IniLogInitialiser( 
	const mr_utils::mr_string&	fileName, 
	const mr_utils::mr_string&	sectionName 
)	: 	m_fileName(fileName),
	m_sectionName(sectionName),
	m_loaded(false) {
}


bool IniLogInitialiser::Load() {
	if (!this->m_loaded) {
		this->m_loaded = m_iniFile.load(this->m_fileName);
	}
	return this->m_loaded;
}


mr_utils::mr_string IniLogInitialiser::GetLogName() {
	return this->GetNodeValue(this->m_sectionName, _L_("OutputName"));
}


mr_utils::mr_string IniLogInitialiser::GetSqlCreateTemplate() {
	return this->GetSyntaxEntry(_L_("CreateTableStmtTemplate"));
}


mr_utils::mr_string IniLogInitialiser::GetSqlDropTemplate() {
	return this->GetSyntaxEntry(_L_("DropTableStmtTemplate"));
}


mr_utils::mr_string IniLogInitialiser::GetSqlInsertTemplate() {
	return this->GetSyntaxEntry(_L_("InsertStmtTemplate"));
}


mr_utils::mr_string IniLogInitialiser::GetOdbcDsnName() {
	return this->GetSyntaxEntry(_L_("DsnName"));
}


mr_utils::mr_string IniLogInitialiser::GetOdbcUserName() {
	return this->GetSyntaxEntry(_L_("User"), false);
}


mr_utils::mr_string IniLogInitialiser::GetOdbcAUthorisationStr() {
	return this->GetSyntaxEntry(_L_("AuthorisationString"), false);
}


int IniLogInitialiser::GetOdbcVersion() {
	/// @todo Create robust conversion routine
	mr_utils::mr_string s = this->GetSyntaxEntry(_L_("ODBCVersion"));
	mr_utils::mr_stringstream os;
	os << s;
	int i;
	os >> i;
	return i;

}


int IniLogInitialiser::GetOdbcConnectTimeout() {
	/// @todo Create robust conversion routine
	mr_utils::mr_string s = this->GetSyntaxEntry(_L_("ConnectTimeoutSeconds"));
	mr_utils::mr_stringstream os;
	os << s;
	int i;
	os >> i;
	return i;
}


mr_utils::mr_string IniLogInitialiser::GetStringDelimiter(bool emptyErr) {
	return this->GetSyntaxEntry(_L_("StringDelimiter"), emptyErr );
}


mr_utils::mr_string IniLogInitialiser::GetFieldDelimiter() {
	return this->GetSyntaxEntry(_L_("FieldDelimiter"));
}


bool IniLogInitialiser::GetOverwriteLogFlag() {
	mr_utils::mr_string flag = this->GetNodeValue(this->m_sectionName, _L_("Overwrite"));

	/// @todo	Need to make this more robust.
	return flag.compare(_L_("true")) == 0;
}


bool IniLogInitialiser::GetUseAutoGenUniqueTableName() {
	mr_utils::mr_string flag = this->GetNodeValue(this->m_sectionName, _L_("AutoGenUniqueFileName"));

	/// @todo	Need to make this more robust.
	return flag.compare(_L_("true")) == 0;
}


mr_utils::mr_string IniLogInitialiser::GetSummaryLogId() {
	return this->GetNodeValue(this->m_sectionName, _L_("SummaryOutputName"), false );
}


mr_utils::mr_string IniLogInitialiser::GetOutputType() {
	return this->GetNodeValue(this->m_sectionName, _L_("OutputType") );
}


mr_utils::mr_string IniLogInitialiser::GetLogType() {
	return this->GetNodeValue(this->m_sectionName, _L_("LogType"));
}


std::vector<mr_utils::mr_string> IniLogInitialiser::GetLogList() {
	// Find the section.
	mr_inireader::iniFile::SectionIterator it = this->GetSection(_L_("LogList"));

	std::vector<mr_utils::mr_string> logs;
	std::for_each(it->nodes().begin(), it->nodes().end(), PopulateLogList(logs));

	if (logs.empty()) {
		this->ThrowError( 
			this->GetNodeValue(this->m_sectionName, _L_("LogList")), 
			L(""), 
			L("There are no valid entries for loggers to log the tests"));
	}
	return logs;
}


mr_utils::mr_string IniLogInitialiser::GetSyntaxEntry( 
	const mr_utils::mr_string&	nodeName, 
	bool						fatalErr 
) {
	return this->GetNodeValue( 
		this->GetNodeValue(this->m_sectionName, _L_("OutputSyntax"), fatalErr),
		nodeName,
		fatalErr
	);
}


mr_utils::mr_string IniLogInitialiser::GetNodeValue( 
	const mr_utils::mr_string& sectionName, 
	const mr_utils::mr_string& nodeName, 
	bool						emptyErr,
	bool						foundErr 
) {
	if (!this->GetSection(sectionName)->nodeExists(nodeName) && foundErr) {
		this->ThrowError(sectionName, nodeName, _L_("not found"));
	}

	mr_utils::mr_string str = this->m_iniFile.getValue( sectionName, nodeName );
	if (str.empty() && emptyErr) {
		this->ThrowError(sectionName, nodeName, _L_("has no value after '='"));
	}
	return str;
}


mr_inireader::iniFile::SectionIterator IniLogInitialiser::GetSection( 
	const mr_utils::mr_string& sectionName) {
	mr_inireader::iniFile::SectionIterator it = this->m_iniFile.getSection(sectionName);
	if (it == this->m_iniFile.sections().end() || (!it->isDataSection())) {
		this->ThrowError(sectionName, L(""), _L_("section not found"));
	}
	return it;
}


FieldVector IniLogInitialiser::GetFields() {
	mr_inireader::iniFile::SectionIterator it = 
		this->GetSection(this->GetNodeValue(this->m_sectionName, _L_("FieldList")));

	FieldVector fields;
	std::for_each( 
		it->nodes().begin(), it->nodes().end(), PopulateFieldListFromIni(fields) 
	);

	if (fields.empty()) {
		this->ThrowError( 
			this->GetNodeValue(this->m_sectionName, _L_("FieldList")), 
			_L_(""), 
			_L_("There are no valid entries for fields that require logging"));
	}
	return fields;
}


void IniLogInitialiser::ThrowError( 
	const mr_utils::mr_string&	sectionName, 
	const mr_utils::mr_string&	nodeName, 
	const mr_utils::mr_string&	msg 
)
{
	mr_utils::mr_stringstream os;
	os << _L_("[") << sectionName << _L_("] ") << nodeName << _L_(" ") << msg;
	mr_utils::mr_exception::assertCondition(false, _FL_, os.str());
}



} //end namespace

