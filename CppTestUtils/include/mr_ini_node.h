///--------------------------------------------------------------------------------------
/// @file	mr_ini_node.h
/// @brief	Ini file node which is the key value pair unit in a section.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_INI_NODE_H)
#define MR_INI_NODE_H


#include "CppTestUtilsDefine.h"
#include "mr_string.h"
#include "mr_iostream.h"
#include "mr_iniInputLine.h"
#include "mr_ini_node.h"


namespace mr_inireader
{


/// @brief	Defines if the line is legitimate data or a comment, white space or garbage.
typedef enum _dataType
{
	NON_DATA,	///< Enum value NON_DATA Indicates that the node holds a valid key value pair.
	VALID_DATA	///< Enum value VALID_DATA  Indicates that the node is a placeholder for comments or garbage.
} LINE_TYPE; ///< enum variable.


///--------------------------------------------------------------------------------------
///
/// @brief	Node class that encapsulates a key value pair node of an ini section.
///
///--------------------------------------------------------------------------------------
class CPPTESTUTILS_API node
{
public:

	/// @brief	Constructor.
	///
	/// @param	inLIne	The iniInputLine that constains the node datat.
	node( const iniInputLine& inLine );


	/// @brief	Copy Constructor.
	///
	/// @param	obj	The node used to construct this node.
	node( const node& obj );


	/// @brief	Assignement operator.
	///
	/// @param	obj	The node used to initialise this node.
	node& operator = ( const node& rhs );


	/// @brief	The value of the node.  It will be blank if the node is not a data node.
	///
	/// @return	The value of the node.
	const mr_utils::mr_string& value() const;


	/// @brief	Holds the key portion of the key value pair or the garbage string if the 
	///			node is not a valid data node.
	///
	/// @return	The key name if valid or the garbage string.
	const mr_utils::mr_string& name() const;


	/// @brief	Returns whether the node is a valid data node or not.
	///
	/// @return	true if the node is a valid data node, otherwise false.
	bool isDataNode() const;


	/// @brief	Default constructor in private scope prevent default construction.
	node();

private:


	/// @brief	Initialise the object with the values from another object.
	///
	/// @param	obj	The object that has the values used to initialise this object.
	void init( const node& obj );

private:

	mr_utils::mr_string m_name;		///< Node name or non data value string.
	mr_utils::mr_string m_value;	///< Node value.
	LINE_TYPE			m_type;		///< Defines if content is data.

};


/// @brief	Streaming function for node object.
///
/// @param	os		The output stream.
/// @param	theNode	The node object to stream out.
///
/// @return	The output stream object.
mr_utils::mr_ostream& operator << ( mr_utils::mr_ostream& os, const node& theNode );


}


#endif