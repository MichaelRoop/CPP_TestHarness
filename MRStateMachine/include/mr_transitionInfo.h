///--------------------------------------------------------------------------------------
/// @file	mr_transitionInfo.h
/// @brief	classes to store and handle state transition information.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_TRANSITION_INFO_H)
#define MR_TRANSITION_INFO_H

//#include "mr_defines.h"
//#include "mr_exception.h"
#include <algorithm>


namespace mr_sm
{

template <class T> struct findTransition; ///< Forward declaration of functor.


typedef enum
{
	NO_INFO,
//	NO_CHANGE,
	STATE_CHANGE,
	SUBSTATE_EXIT

} TRANSITION_TYPE;


template <class T> class mr_state;


///--------------------------------------------------------------------------------------
///
///	@brief	
///
///
/// This class encapsulates 
///
///
///--------------------------------------------------------------------------------------
template <class T> 
class mr_transitionInfo
{
public:

	mr_transitionInfo( unsigned int id, TRANSITION_TYPE type, mr_state<T>* nextState = NULL ) :
	  m_id( id ),
	  m_type( type ),
	  m_nextState( nextState )
	  {
	  }


	unsigned int	m_id;			///< Either an event or result identifier.
	unsigned int	m_type;			///< Type of info.
	mr_state<T>*	m_nextState;	///< Next state for transition.
};


//----------------------------------------------------------
/// @Functor to find if the transition is registered.
template<class T>
struct findTransition
{
	findTransition( unsigned int target ) : m_target( target ) {}

	bool operator ()( const mr_transitionInfo<T>& ti ) const
	{
		return ti.m_id == m_target;
	}
	unsigned int m_target; ///< Target transition identifier.
};



} // end namespace.

#endif