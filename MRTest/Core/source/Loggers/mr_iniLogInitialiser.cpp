///--------------------------------------------------------------------------------------
/// @file	mr_iniLogInitialiser.cpp
/// @brief	Abstracts the retrieval of the intialisation data for the log object from ini
///			file.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_iniLogInitialiser.h"
#include "mr_exception.h"
#include "mr_defines.h"
#include "mr_sstream.h"
#include <algorithm>


namespace mr_test
{

/// @brief	Functor to populate field vector from ini.
struct populateFieldListFromIni
{
	populateFieldListFromIni( FieldVector& fields ) : m_fields( fields )
	{
	}

	void operator () ( const mr_inireader::node& theNode )
	{
		if (theNode.isDataNode())
		{
			m_fields.push_back( FieldPair( theNode.name(), theNode.value() ) );
		}
	}
private:
	FieldVector& m_fields;	///< receiving vector of fields.

};


/// @brief	Functor to populate field vector from ini.
struct populateLogList
{
	populateLogList( std::vector<mr_utils::mr_string>& logs ) : m_logs( logs ) {}

	void operator () ( const mr_inireader::node& theNode )
	{
		if (theNode.isDataNode())
		{
			m_logs.push_back( theNode.value() );
		}
	}
private:
	std::vector<mr_utils::mr_string>& m_logs;	///< receiving vector of log names.

};
//----------------- End Functors -----------------------------------


iniLogInitialiser::iniLogInitialiser( 
	const std::string&			fileName, 
	const mr_utils::mr_string&	sectionName 
)	
: 	m_fileName( fileName ),
	m_sectionName( sectionName ),
	m_loaded( false )

{
}


bool iniLogInitialiser::load()
{
	if (!m_loaded)
	{
		m_loaded = m_iniFile.load( m_fileName );
	}
	return m_loaded;
}


mr_utils::mr_string iniLogInitialiser::getLogName()
{
	return this->getNodeValue( m_sectionName, L("OutputName") );
}


mr_utils::mr_string iniLogInitialiser::getSqlCreateTemplate()
{
	return this->getSyntaxEntry( L("CreateTableStmtTemplate") );
}


mr_utils::mr_string iniLogInitialiser::getSqlDropTemplate()
{
	return this->getSyntaxEntry( L("DropTableStmtTemplate") );
}


mr_utils::mr_string iniLogInitialiser::getSqlInsertTemplate()
{
	return this->getSyntaxEntry( L("InsertStmtTemplate") );
}


mr_utils::mr_string iniLogInitialiser::getOdbcDsnName()
{
	return this->getSyntaxEntry( L("DsnName") );
}


mr_utils::mr_string iniLogInitialiser::getOdbcUserName()
{
	return this->getSyntaxEntry( L("User"), false );
}


mr_utils::mr_string iniLogInitialiser::getOdbcAUthorisationStr()
{
	return this->getSyntaxEntry( L("AuthorisationString"), false );
}


int iniLogInitialiser::getOdbcVersion()
{
	/// @todo Create robust conversion routine
	mr_utils::mr_string s = this->getSyntaxEntry( L("ODBCVersion") );
	mr_utils::mr_stringstream os;
	os << s;
	int i;
	os >> i;
	return i;

}


int iniLogInitialiser::getOdbcConnectTimeout()
{
	/// @todo Create robust conversion routine
	mr_utils::mr_string s = this->getSyntaxEntry( L("ConnectTimeoutSeconds") );
	mr_utils::mr_stringstream os;
	os << s;
	int i;
	os >> i;
	return i;
}


mr_utils::mr_string iniLogInitialiser::getStringDelimiter( bool emptyErr )
{
	return this->getSyntaxEntry( L("StringDelimiter"), emptyErr  );
}


mr_utils::mr_string iniLogInitialiser::getFieldDelimiter()
{
	return this->getSyntaxEntry( L("FieldDelimiter") );
}


bool iniLogInitialiser::getOverwriteLogFlag()
{
	mr_utils::mr_string flag = this->getNodeValue( m_sectionName, L("Overwrite") );

	/// @todo	Need to make this more robust.
	return flag.compare( L("true") ) == 0;
}


bool iniLogInitialiser::getUseAutoGenUniqueTableName()
{
	mr_utils::mr_string flag = this->getNodeValue( m_sectionName, L("AutoGenUniqueFileName") );

	/// @todo	Need to make this more robust.
	return flag.compare( L("true") ) == 0;
}



mr_utils::mr_string iniLogInitialiser::getSummaryLogId()
{
	return this->getNodeValue( m_sectionName, L("SummaryOutputName"), false );
}


mr_utils::mr_string iniLogInitialiser::getOutputType()
{
	return this->getNodeValue( m_sectionName, L("OutputType") );
}


mr_utils::mr_string iniLogInitialiser::getLogType()
{
	return this->getNodeValue( m_sectionName, L("LogType") );
}


std::vector<mr_utils::mr_string> iniLogInitialiser::getLogList()
{
	// Find the section.
	mr_inireader::iniFile::SectionIterator it = this->getSection( L("LogList") );

	std::vector<mr_utils::mr_string> logs;
	std::for_each( it->nodes().begin(), it->nodes().end(), populateLogList( logs ) );

	if (logs.empty())
	{
		this->throwError( 
			this->getNodeValue( m_sectionName, L("LogList") ), 
			L(""), 
			L("There are no valid entries for loggers to log the tests") );
	}
	return logs;
}


mr_utils::mr_string iniLogInitialiser::getSyntaxEntry( 
	const mr_utils::mr_string&	nodeName, 
	bool						fatalErr 
)
{
	return this->getNodeValue( 
		this->getNodeValue( m_sectionName, L("OutputSyntax"), fatalErr ),
		nodeName,
		fatalErr
	);
}


mr_utils::mr_string iniLogInitialiser::getNodeValue( 
	const mr_utils::mr_string& sectionName, 
	const mr_utils::mr_string& nodeName, 
	bool						emptyErr,
	bool						foundErr 
)	
{
	if (!this->getSection( sectionName )->nodeExists( nodeName ) && foundErr)
	{
		this->throwError( sectionName, nodeName, L("not found") );
	}

	mr_utils::mr_string str = m_iniFile.getValue( sectionName, nodeName );
	if (str.empty() && emptyErr)
	{
		this->throwError( sectionName, nodeName, L("has no value after '='") );
	}
	return str;
}


mr_inireader::iniFile::SectionIterator iniLogInitialiser::getSection( 
	const mr_utils::mr_string& sectionName 
)
{
	mr_inireader::iniFile::SectionIterator it = m_iniFile.getSection( sectionName );
	if (it == m_iniFile.sections().end() || (!it->isDataSection()))
	{
		this->throwError( sectionName, L(""), L("section not found") );
	}
	return it;
}


FieldVector iniLogInitialiser::getFields()
{
	mr_inireader::iniFile::SectionIterator it = 
		this->getSection( this->getNodeValue( m_sectionName, L("FieldList") ) );

	FieldVector fields;
	std::for_each( 
		it->nodes().begin(), it->nodes().end(), populateFieldListFromIni( fields ) 
	);

	if (fields.empty())
	{
		this->throwError( 
			this->getNodeValue( m_sectionName, L("FieldList") ), 
			L(""), 
			L("There are no valid entries for fields that require logging") );
	}
	return fields;
}


void iniLogInitialiser::throwError( 
	const mr_utils::mr_string&	sectionName, 
	const mr_utils::mr_string&	nodeName, 
	const mr_utils::mr_string&	msg 
)
{
	mr_utils::mr_stringstream os;
	os << L("[") << sectionName << L("] ") << nodeName << L(" ") << msg;
	mr_utils::mr_exception::assertCondition( false, FL, os.str() );
}



} //end namespace

