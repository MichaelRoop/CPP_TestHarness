///--------------------------------------------------------------------------------------
/// @file	mr_ini_file.cpp
/// @brief	Ini file reader.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#include "mr_ini_file.h"
#include "mr_char.h"
#include "mr_fstream.h"
#include "mr_functors.h"
#include "mr_toStream.h"
#include "mr_sstream.h"
#include "mr_exception.h"
#include "mr_defines.h"
#include "mr_iniInputLine.h"

#include <algorithm>


namespace mr_inireader {


/// @brief	Filter out non valid sections to produce a good set of sections.
struct FilterSectionsFunctor {
	FilterSectionsFunctor( iniFile::SectionVector& sectionVec ) : m_sections( sectionVec ) {}

	void operator () (const section& theSection) {
		if (theSection.isDataSection()) {
			m_sections.push_back( theSection );
		}
	}
	iniFile::SectionVector& m_sections; ///< Target for sections.
};
// -------------------- end functors ----------------

iniFile::iniFile() {
}


iniFile::iniFile(const mr_utils::mr_string& filename) : m_filename(filename) {
}


iniFile::iniFile(const iniFile& obj) {
	this->init( obj );
}


iniFile& iniFile::operator = (const iniFile& rhs) {
	if (this != &rhs) {
		this->init( rhs );
	}
	return *this;
}


void iniFile::init(const iniFile& obj) {
	m_sections.clear();
	m_sections = obj.m_sections;
	m_filename = obj.m_filename;
}


bool iniFile::load(const mr_utils::mr_string& filename) {
	m_sections.clear();
#if defined(_WIN32)
    // The wchar_t for filename is a MS extension
    mr_utils::mr_ifstream  script(filename.c_str());
#else
    mr_utils::mr_ifstream  script(mr_utils::ToCharPtr(filename).c_str());
#endif

	mr_utils::mr_stringstream ss;
	mr_utils::ToStream( ss, filename ) << L( " cannot be opened" );
	mr_utils::mr_exception::assertCondition( script.is_open(), FL, ss.str() );

	const int size = 2048;
	std::vector<mr_utils::mr_char> buff;
	buff.assign( size + 1, L('\0') );
	section			workingSection;
	iniInputLine	inLine;

	while (script.getline(&buff[0], size)) {
		inLine.init( mr_utils::mr_string( &buff[0] ) );

		switch (inLine.type()) {
		case iniInputLine::SECTION:
			this->addSection( workingSection );
			workingSection.setName( inLine.firstValue() );
			break;
		default:
			if (workingSection.name().empty()) {
				// Text lines before the first section is detected will be written as non data 
				// sections representing comments and garbage lines.
				this->addSection( section( inLine ) );
			}
			else {
				workingSection.addNode( inLine );
			}
			break;
		}
	}

	// Add the last section built before leaving.
	this->addSection( workingSection );

	return true;

}


bool iniFile::addSection(const section& theSection) {
	if (!theSection.name().empty()) {
		m_sections.push_back( theSection );
		return true;
	}
	return false;
}


const mr_utils::mr_string& iniFile::name() const {
	return m_filename;
}


iniFile::SectionIterator iniFile::getSection(const mr_utils::mr_string& name) {
	return 
		std::find_if( 
			m_sections.begin(), 
			m_sections.end(), 
			mr_utils::isNamed<section,mr_utils::mr_string>( name ) 
		);
}


bool iniFile::sectionExists(const mr_utils::mr_string& name) {
	SectionIterator it = this->getSection( name );
	if (it == m_sections.end() || !it->isDataSection()) {
		return false;
	}
	return true;
}


bool iniFile::nodeExists( 
	const mr_utils::mr_string& sectionName, 
	const mr_utils::mr_string& nodeName) {
	if (this->sectionExists(sectionName)) {
		return this->getSection( sectionName )->nodeExists( nodeName );
	}
	return false;
}


mr_utils::mr_string iniFile::getValue( 
	const mr_utils::mr_string& sectionName, 
	const mr_utils::mr_string& nodeName) {
	SectionIterator it = this->getSection( sectionName );
	return it == this->sections().end() ? mr_utils::mr_string( L("") ) : it->value( nodeName );
}


const iniFile::SectionVector& iniFile::sections() const {
	return m_sections;
}


iniFile::SectionVector iniFile::getSectionsCopy() {
	iniFile::SectionVector sections;
	std::for_each( m_sections.begin(), m_sections.end(), FilterSectionsFunctor( sections ) );
	return sections;
}


section::NodeVector iniFile::getNodesCopy(const mr_utils::mr_string& sectionName) {
	if (this->sectionExists(sectionName)) {
		return this->getSection( sectionName )->getNodesCopy();
	}
	return section::NodeVector();
}


mr_utils::mr_ostream& operator << (mr_utils::mr_ostream& os, const iniFile& obj) {
	std::for_each( 
		obj.sections().begin(), 
		obj.sections().end(), 
		mr_utils::ToStreamClass<section,mr_utils::mr_ostream>(os));
	return os;
}


} // end namespace
