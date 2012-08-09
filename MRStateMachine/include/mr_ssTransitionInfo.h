///--------------------------------------------------------------------------------------
/// @file	mr_ssTransitionInfo.h
/// @brief	classes to store and handle state transition information for super states.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_SS_TRANSITION_INFO_H)
#define MR_SS_TRANSITION_INFO_H

#include "mr_transitionInfo.h"


namespace mr_sm
{

template <class T> struct findSSTransition; ///< Forward declaration of functor.


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
class mr_ssTransitionInfo
{
public:

	mr_ssTransitionInfo( 
		unsigned int stateId, 
		unsigned int result, 
		mr_state<T>* nextState ) :
		m_stateId( id ),
		m_result( result ),
		m_nextState( nextState )
		{
		}

	unsigned int	m_stateId;		///< The current sub state.
	unsigned int	m_result;		///< The result returned from the sub state.
	mr_state<T>*	m_nextState;	///< Next state for transition.
};




//----------------------------------------------------------
/// @brief	Functor to find if there is a transition registered for a result from a 
///			particular sub state.
///
template<class T>
struct findSSTransition
{
	findSSTransition( unsigned int subStateId, unsigned int result ) : 
		m_subStateId( subStateId ),
		m_result( result )
	{
	}

	bool operator ()( const mr_ssTransitionInfo<T>& ssInfo ) const
	{
		return ssInfo.m_stateId == m_subStateId && ssInfo.m_result == m_result;
	}

	unsigned int m_subStateId;	///< SubState of origine.
	unsigned int m_result;		///< End result code from sub state.
};





} // end namespace.

#endif