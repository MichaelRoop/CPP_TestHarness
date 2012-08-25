///--------------------------------------------------------------------------------------
/// @file	mr_ini_section.h
/// @brief	Ini file node section object.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_INI_SECTION_H)
#define MR_INI_SECTION_H

#include "CrossPlatform.h"
#include "mr_ini_node.h"
#include "mr_iniInputLine.h"

#include <vector>
EXP_TEMPLATE template class CPPTESTUTILS_API std::allocator<mr_inireader::node>;
EXP_TEMPLATE template class CPPTESTUTILS_API std::vector<mr_inireader::node>;


namespace mr_inireader
{

///--------------------------------------------------------------------------------------
///
/// @brief	Class that encapsulates an ini file section.
///
///--------------------------------------------------------------------------------------
class CPPTESTUTILS_API section
{
public:

	/// @typedef	Definition of a vector of nodes.
	typedef std::vector<mr_inireader::node>					NodeVector;

	/// @typedef	Definition of a node vector iterator.
	typedef std::vector<mr_inireader::node>::const_iterator	NodeIterator;


	/// @default constructor.
	section();


	/// @brief	Constructor.
	///
	/// @param	input	The iniInputLine used to create the node.
	section( const iniInputLine& input );


	/// @brief	Copy constructor.
	///
	/// @param	obj	The object used to construct this object.
	section( const section& obj );


	/// @brief	Assignement operator.
	///
	/// @param	obj	The object used to initialise this object.
	///
	/// @return	This object.
	section& operator = ( const section& rhs );


	/// @brief	The name of the section.  Does not contain brackets.
	///
	/// @return	The name of the section.
	const mr_utils::mr_string& name() const;
	

	/// @brief	Indicates if the section object contains data or is a placeholder.
	///
	/// @return	true if it holds data, otherwise false.
	bool isDataSection() const;


	/// @brief	Add a node to the section.
	///
	/// @param	input	The iniInputLine used to create the node.
	void addNode( const iniInputLine& input );


	/// @brief	The objects node vector.
	///
	///	WARNING:	This is an efficiency method.  It does not make a copy 
	///				but exposes the raw vector of nodes.  You must validate 
	///				each node with a call to node::isDataSection.
	///
	/// @return	The vector of nodes held by the section.
	const section::NodeVector& nodes() const;
	

	/// @brief	The value of held by the named node.
	///
	/// @param	nodeName	The name of the node to look up for the value.
	///
	/// @return	The value if found, otherwise and empty string.
	const mr_utils::mr_string& value( const mr_utils::mr_string& nodeName ) const;


	/// @brief	Reset this object.
	void clear();


	/// @brief	Set the name of the section.  All previous nodes are cleared.
	///
	/// It is presumed that the name is greater than zero length.
	///
	/// @param	name	The name of the section.
	void setName( const mr_utils::mr_string& name );


	/// @brief	Retrieve an iterator that points to a named node.
	///
	///	WARNING:	This is an efficiency method.  It does not make a copy 
	///				but exposes the raw vector of nodes.  You must validate
	///				the iterator against nodes().end().  You must also 
	///				validate each node with a call to node::isDataSection.
	///
	/// @param	name	The name of the node to retrieve.
	///
	/// @return	An iterator pointing to the node if found, otherwise an invalid iterator.
	NodeIterator getNode(  const mr_utils::mr_string& name ) const;


	/// @brief	Verifies if a named node exists and is a data node.
	///
	/// @param	name	The name of the node to retrieve.
	///
	/// @return	true if the node exists and is a Data node, otherwise false.
	bool nodeExists(  const mr_utils::mr_string& name ) const;


	/// @brief	Retrieve a copy of the vector of data nodes.
	///
	/// @return	A vector of nodes.
	const NodeVector getNodesCopy() const;

private:

	mr_utils::mr_string					m_name;		///< Node name or non data value string.		
	NodeVector							m_nodes;	///< Vector of nodes.
	LINE_TYPE							m_type;		///< Defines if content is data.
	mr_utils::mr_string					m_dummyVal;	///< Empty dummy value string for not found. 



	/// @brief	Initialise the section.
	///
	/// @param	obj	The object used to initialise this object.
	void init( const section& obj );

};


/// @brief	Streaming function for node object.
///
/// @param	os			The output stream.
/// @param	theSection	The section object to stream out.
///
/// @return	The output stream object.
mr_utils::mr_ostream& operator << ( mr_utils::mr_ostream& os, const section& theSection );

}


#endif