///--------------------------------------------------------------------------------------
/// @file	mr_state.h
/// @brief	State base class.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_STATE_H)
#define MR_STATE_H

#include "mr_defines.h"
#include "mr_exception.h"
#include "mr_transitionInfo.h"


namespace mr_sm
{
	
///--------------------------------------------------------------------------------------
///
///	@brief	Pure virtual base class for states.
///
///	The state object does not own any of the pointers to other states. They are created,
/// and managed by the super state.  The state never accesses these pointers.  It only 
/// passes them back.
///
/// This class encapsulates 
///
/// There are three stages to a states life, On Entry, OnState and OnExit.
///
///--------------------------------------------------------------------------------------
template <class T>
class mr_state
{

private:
	typedef std::vector<mr_transitionInfo<T> >		MR_TRANSITION_VEC;	///< Transition vector.
	typedef typename MR_TRANSITION_VEC::iterator	MR_TRANSITION_IT;	///< Transition vector iterator.

public:

	/// @brief	Constructor
	///
	///	@param	id	State ID.
	mr_state( unsigned int id ) : m_id( id )
	{
	}


	/// @brief	Destructor
	virtual ~mr_state()
	{
	}


	/// @brief	Return the state Id.
	unsigned int Id() const
	{
		return m_id;
	}


	/// @brief	Register a pre-emptive state change to happen on an event ID. The internal 
	///			OnState code of the state will not be executed.
	///
	///	@param	id		The event id.
	/// @param	state	The state to transition to on event id.
	void RegisterEventTransition( unsigned int id, TRANSITION_TYPE type, mr_state* state )
	{		
		this->AssertNotRegistered( m_eTransitions, id, FL );
		m_eTransitions.push_back( mr_transitionInfo( id, type, state ) );
	}


	/// @brief	Register a state change to happen as a result of internally returned ID from
	///			the body of the OnState code.
	///
	///	@param	id		The event id.
	/// @param	state	The state to transition to on the result id.
	void RegisterResultTransition( unsigned int id, TRANSITION_TYPE type, mr_state* state )
	{
		this->AssertNotRegistered( m_rTransitions, id, FL );
		m_rTransitions.push_back( mr_transitionInfo( id, type, state ) );
	}


	/// @brief	Pulse the state for it to execute its code.
	///
	/// @param	Tevent	The event to push at the state.
	///
	/// @return NULL if no state change required, otherwise the new state.
	virtual mr_transitionInfo<T> PulseState( const T& _event )
	{
		// Check for pre-emptive, then results.
		mr_transitionInfo<T> info = this->GetEventTransition( _event.m_id );
		if (info.m_type == NO_INFO)
		{
			info = this->GetResultsTransition( this->OnState( _event ) );
		}
		return info;
	}


	virtual void OnEntry()
	{
	}


	virtual unsigned int OnState( const T& event ) = 0;


	virtual void OnExit()
	{
	}


protected:


	/// @brief	Retrieves the pre-emptive event next state based on an event id.
	///
	/// @param	id	The id of the event.
	///
	/// @return	The next state to transition to or NULL if no matching id.
	mr_transitionInfo<T> GetEventTransition( int id )
	{
		return this->GetTransition( m_eTransitions, id );
	}


	/// @brief	Retrieves the next state based on a result id.
	///
	/// @param	id	The id of the result.
	///
	/// @return	The next state to transition to or NULL if no matching id.
	mr_transitionInfo<T> GetResultsTransition( int id )
	{
		return this->GetTransition( m_rTransitions, id );
	}


private:

	unsigned int		m_id;			///< State ID.
	MR_TRANSITION_VEC	m_eTransitions;	///< possible transitions before any state code execution.
	MR_TRANSITION_VEC	m_rTransitions;	///< possible transitions from internal code execution.


	/// @brief	Register a pre-emptive state change to happen on an event ID. The internal 
	///			OnState code of the state will not be executed.
	///
	///	@param	id		The event id.
	/// @param	state	The state to transition to on event id.
	void AssertNotRegistered( MR_TRANSITION_VEC& vec, int id, const char* file, int line ) const
	{
		mr_utils::mr_exception::assertCondition( 
			std::find_if( vec.begin(), vec.end(), findTransition<T>( id ) ) == vec.end(), 
			file, 
			line, 
			L("Already registered") 
		);
	}


	/// @brief	Retrieves the next state based on an id.
	///
	/// @param	id	The id of the event or result.
	///
	/// @return	The next state to transition to or NULL if no matching id.
	mr_transitionInfo<T> GetTransition( MR_TRANSITION_VEC& vec, int id )
	{
		MR_TRANSITION_IT it = std::find_if( vec.begin(), vec.end(), findTransition<T>( id ) );
		if (it != vec.end())
		{
			return *it;
		}
		return mr_transitionInfo<T>( id, NO_INFO );
	}


	/// @brief	Protected default constructor to force use of regular constructor.
	mr_state() ;


	/// @brief	Protected copy constructor to force use of regular constructor.
	///
	/// @param	tc	The mr_state used for construction.
	mr_state( const mr_state& tc );


	/// @brief	Assignement operator in private scope to preven assignments.
	///
	/// @param	tc	The mr_state used for construction.
	mr_state& operator = ( const mr_state& tc );

};

} // end namespace.

#endif