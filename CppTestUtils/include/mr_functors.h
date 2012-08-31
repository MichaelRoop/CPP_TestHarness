///--------------------------------------------------------------------------------------
/// @file	mr_functors.h
/// @brief	Functors that are generic enough to be used across a widely.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_FUNCTORS_H)
#define MR_FUNCTORS_H

#include "CppTestUtilsDefine.h"
#include "mr_exception.h"
#include "mr_defines.h"
#include "string.h" //memcpy

#include <vector>


namespace mr_utils
{

///--------------------------------------------------------------------------------------
/// @brief	Functor to delete each pointer on iteration.
///
	/// You can use this with the std::for each to delete out a container of pointers.
template<class T>
struct DeletePtr
{
	/// @brief	Function operator called on each iteration.
	///
	/// @param	ptr	The pointer to delete.
	void operator () ( T* ptr )
	{
		if (ptr)
		{
			delete ptr;
			ptr = 0;
		}
	}
};


///--------------------------------------------------------------------------------------
///
/// @brief	Functor to convert from wide to narrow char.  
///
/// This functor is only good for the ANSII range.  No Unicode conversion is done.
/// Assume null terminator already in wchar_t string.
///
///--------------------------------------------------------------------------------------
struct CPPTESTUTILS_API AnsiiWideCharToNarrow
{

	/// @brief	Constructor.
	///
	/// Pass this functor to the for_each algorithm to convert a vector of wide char.
	///
	/// @param	output	A vector of narrow char to receive the converted characters.  It must
	///					already be sized to the same length as the container of wide chars 
	///					being converted.
	AnsiiWideCharToNarrow( std::vector<char>& output ) 
	:	m_output( output ), 
		m_pos( 0 ) 
	{
	}


	/// @brief	Function operator called for every element in the container.
	///
	/// @exception	mr_exception if the chars to convert exceeds the size of the receptor 
	///				vector.
	///
	/// @param	c	The character to be converted to narrow.
	void operator () ( const wchar_t& c )
	{
		mr_exception::assertCondition( m_pos < m_output.size(), FL, L("Exceeded receptor limits") );

		/// @todo This assumes windows 16 bit wchar_t. Add compiler switch for NIX 32 bit.
		/// also, first 8 bits contains char.  Is this an Endian thing?
		std::vector<char> buff( 2, '\0' );
		memcpy( &buff[0], &c, 2 );
		m_output[m_pos++] = buff[0];
	}

private:
	std::vector<char>&				m_output;	///< Vector to receive converted chars.
	std::vector<char>::size_type	m_pos;		///< Current position in string conversion.


	/// @brief	Assignment operator to satisfy compiler warnings.
	AnsiiWideCharToNarrow& operator = ( const AnsiiWideCharToNarrow& rhs )
	{
		if (&rhs != this)
		{
			m_output	= rhs.m_output;
			m_pos		= rhs.m_pos;
		}
		return *this;
	}

};



///--------------------------------------------------------------------------------------
///
/// @brief	Functor to convert from narrow to wide char.  
///
///--------------------------------------------------------------------------------------
struct CPPTESTUTILS_API NarrowCharToWide
{

	/// @brief	Constructor.
	///
	/// Pass this functor to the for_each algorithm to convert a vector of narrow char.
	///
	/// @param	output	A vector of wide char to receive the converted characters.  It must
	///					already be sized to the same length as the container of narrow chars 
	///					being converted.
	NarrowCharToWide( std::vector<wchar_t>& output ) 
	:	m_output( output ), 
		m_pos( 0 ) 
	{
	}


	/// @brief	Function operator called for every element in the container.
	///
	/// @exception	mr_exception if the chars to convert exceeds the size of the receptor 
	///				vector.
	///
	/// @param	c	The character to be converted to wide.
	void operator () ( const char& c )
	{
		mr_exception::assertCondition( m_pos < m_output.size(), FL, L("Exceeded receptor limits") );

		/// @todo  Note: this assumes windows 16 bit wchar_t. Add compiler switch for NIX 32 bit.
		/// also, first 8 bits contains char.  Is this an Endian thing?
		std::vector<wchar_t> buff( 1, '\0' );
		memcpy( &buff[0], &c, 1 );
		m_output[m_pos++] = buff[0];
	}

private:
	std::vector<wchar_t>&				m_output;	///< Vector to receive converted chars.
	std::vector<wchar_t>::size_type		m_pos;		///< Current position in string conversion.


	/// @brief	Assignment operator to satisfy compiler warnings.
	NarrowCharToWide& operator = ( const NarrowCharToWide& rhs )
	{
		if (&rhs != this)
		{
			m_output	= rhs.m_output;
			m_pos		= rhs.m_pos;
		}
		return *this;
	}

};


///--------------------------------------------------------------------------------------
//
/// @brief	Functor that will do a name comparison on all objects in a container.
///
/// The object must have a name() method for this to work.
///
///	@tparam	The object to do a name lookup on.
//
///--------------------------------------------------------------------------------------
template<class T, class T2>
class isNamed
{
public:

	/// @brief	Constructor.
	///
	/// @param	name	The name to compare through the iterations.
	isNamed( const T2& name ) : m_name( name ) 
	{ 
	}


	/// @brief	Function operator.
	///
	/// @param	theObj	The current object in the iteration.
	///
	/// @return	true if the name matches, otherwise false.
	bool operator () ( const T& theObj ) 
	{ 
		return theObj.name() == m_name; 
	}

private:

	const T2& m_name;	///< The comparison name.
};




}


#endif