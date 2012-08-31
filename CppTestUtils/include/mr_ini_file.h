///--------------------------------------------------------------------------------------
/// @file	mr_ini_file.h
/// @brief	Ini file reader.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_INI_FILE_H)
#define MR_INI_FILE_H

#include "CppTestUtilsDefine.h"
#include "mr_ini_section.h"

#include <vector>
EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator<mr_inireader::section>;
EXP_TEMPLATE template class CPPTESTUTILS_API std::vector<mr_inireader::section>;



namespace mr_inireader
{

/// @brief	Ini file reader.
class CPPTESTUTILS_API iniFile
{
public:

	typedef std::vector<mr_inireader::section>					SectionVector;
	typedef std::vector<mr_inireader::section>::iterator			SectionIterator;


	/// @brief	Constructor.
	iniFile( );


	/// @brief	Constructor.
	///
	/// @param	filename	The name of the ini file.
	iniFile( const std::string& filename );


	/// @brief	Copy constructor.
	///
	/// @param	obj	The iniFile object used to construct this object.
	iniFile( const iniFile& obj );


	/// @brief	Assignment operator.
	///
	/// @param	rhs	The iniFile object used to initialise this object.
	iniFile& operator = ( const iniFile& rhs );


	/// @brief	Load the ini file into the object.
	///
	/// @param	filename	The name of the ini file.
	///
	/// @return	true if the load was successful, otherwise false.
	bool load( const std::string& filename );


	/// @brief	The ini file name.
	///
	/// @return	The ini file name.
	const std::string& name() const;


	/// @brief	Retrieves the named section.
	///
	///	WARNING:	This is an efficiency method.  It does not make a copy 
	///				but exposes the raw vector of sections.  You must validate
	///				the iterator against sections().end().  You must also 
	///				validate each section with a call to section::isDataSection.
	///
	/// @param	name	The name of the section to retrieve.
	///
	/// @return The retrieved section 
	SectionIterator getSection( const mr_utils::mr_string& name );


	/// @brief	Verifies if named section exists.
	///
	/// @param	name	The name of the section to check.
	///
	/// @return true if it exists and is a data section, otherwise false.
	bool sectionExists( const mr_utils::mr_string& name );


	/// @brief	Verifies if named node from a named section exists.
	///
	/// @param	sectionName	The name of the section to check.
	/// @param	nodeName	The name of the node to check.
	///
	/// @return true if it exists and is a data section, otherwise false.
	bool nodeExists( const mr_utils::mr_string& sectionName, const mr_utils::mr_string& nodeName );


	/// @brief	Retrieves value from the named section and key.
	///
	/// @param	sectionName	name of the section to retrieve.
	/// @param	nodeName	name of the node that holds the value to retrieve.
	///
	/// @return	The retrieved value or an empty string if not found. 
	mr_utils::mr_string getValue( 
		const mr_utils::mr_string& sectionName, 
		const mr_utils::mr_string& nodeName 
	);


	/// @brief	Add a section to the ini file.
	///
	/// @param	theSection	The section to add.
	///
	/// @return	true if successful, otherwise false.
	bool addSection( const section& theSection );


	/// @brief	Retrieve a reference to the vector of sections.
	///
	///	WARNING:	This is an efficiency method.  It does not make a copy 
	///				but exposes the raw vector of sections.  You must validate 
	///				each section with a call to section::isDataSection.
	///
	/// @return	A reference to the vector of sections.
	const SectionVector& sections() const;


	/// @brief	Retrieve a copy of the vector of data sections.
	///
	/// @return	A vector of sections.
	SectionVector getSectionsCopy();


	/// @brief	Retrieve a copy of the vector of data nodes from the named section.
	///
	/// @param	sectionName	name of the section to retrieve.
	///
	/// @return	A vector of nodes.
	section::NodeVector getNodesCopy( const mr_utils::mr_string& sectionName );


private:

	std::string			m_filename;	///< File name of the ini file.
	SectionVector		m_sections;	///< vector of sections.


	/// @brief	Initialise the ini file with another ini file.
	///
	/// @param	obj	The iniFile to use for its values.
	void init( const iniFile& obj );

};


/// @brief	Streaming function for node object.
///
/// @param	os	The output stream.
/// @param	obj	The iniFile object to stream out.
///
/// @return	The output stream object.
mr_utils::mr_ostream& operator << ( mr_utils::mr_ostream& os, const iniFile& obj );


}

#endif