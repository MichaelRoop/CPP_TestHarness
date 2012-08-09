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

#include "mr_exception.h"
#include <algorithm>



namespace mr_sm
{

//template <class T> struct findTransition; ///< Forward declaration of functor.


template <class T> struct zfindTransition; ///< Forward declaration of functor.


typedef enum
{
	NO_CHANGE,
	STATE_CHANGE,
	SUBSTATE_EXIT

} TRANSITION_TYPE;


template <class T> class mr_state;


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

	unsigned int	m_id;
	unsigned int	m_type;
	mr_state<T>*	m_nextState;
};


//
//
//template <class T> 
//class mr_transitionResult
//{
//public:
//	mr_transitionResult( unsigned int id, unsigned int type, T* nextState ) :
//	  m_id( id ),
//	  m_type( type ),
//	  m_nextState( nextState )
//	  {
//	  }
//
//	unsigned int	m_id;
//	unsigned int	m_type;
//	T*				m_nextState;
//};




	
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
public:

	typedef std::vector<mr_transitionInfo<T> >		zMR_TRANSITION_VEC;	///< Transition vector.


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

//////////////////////////////////////////////////////////////////////////

	/// @brief	Register a pre-emptive state change to happen on an event ID. The internal 
	///			OnState code of the state will not be executed.
	///
	///	@param	id		The event id.
	/// @param	state	The state to transition to on event id.
	void zAssertNotRegistered( zMR_TRANSITION_VEC& vec, int id, const char* file, int line ) const
	{
		mr_utils::mr_exception::assertCondition( 
			std::find_if( vec.begin(), vec.end(), zfindTransition<T>( id ) ) == vec.end(), 
			file, 
			line, 
			L("Already registered") 
		);
	}


	/// @brief	Register a pre-emptive state change to happen on an event ID. The internal 
	///			OnState code of the state will not be executed.
	///
	///	@param	id		The event id.
	/// @param	state	The state to transition to on event id.
	void zRegisterEventEarlyTransition( unsigned int id, TRANSITION_TYPE type, mr_state* state )
	{		
		this->zAssertNotRegistered( m_evEarlyTransitions, id, FL );
		zm_evEarlyTransitions.push_back( mr_transitionInfo( id, type, state ) );
	}


	/// @brief	Register a state change to happen on an event ID after internal OnState
	///			code of the state is executed and returns a 0 results transition.
	///
	///	@param	id		The event id.
	/// @param	state	The state to transition to on event id.
	void zRegisterEventLateTransition( unsigned int id, TRANSITION_TYPE type, mr_state* state )
	{
		this->zAssertNotRegistered( zm_evLateTransitions, id, FL );
		zm_evLateTransitions.push_back( mr_transitionInfo( id, type, state ) );
	}


	/// @brief	Register a state change to happen as a result of internally returned ID from
	///			the body of the OnState code.
	///
	///	@param	id		The event id.
	/// @param	state	The state to transition to on the result id.
	void RegisterResultTransition( unsigned int id, TRANSITION_TYPE type, mr_state* state )
	{
		this->zAssertNotRegistered( zm_rTransitions, id, FL );
		zm_rTransitions.push_back( mr_transitionInfo( id, type, state ) );
	}





//////////////////////////////////////////////////////////////////////////

	///// @brief	Register a pre-emptive state change to happen on an event ID. The internal 
	/////			OnState code of the state will not be executed.
	/////
	/////	@param	id		The event id.
	///// @param	state	The state to transition to on event id.
	//void AssertNotRegistered( const mr_state* state, const char* file, int line ) const
	//{
	//	mr_utils::mr_exception::assertCondition( state != NULL, file, line, L("Already registered") );
	//}


	///// @brief	Register a pre-emptive state change to happen on an event ID. The internal 
	/////			OnState code of the state will not be executed.
	/////
	/////	@param	id		The event id.
	///// @param	state	The state to transition to on event id.
	//void RegisterEventEarlyTransition( unsigned int id, mr_state* state )
	//{		
	//	this->AssertNotRegistered( this->GetEventEarlyTransition( id ), FL );
	//	m_evEarlyTransitions.push_back( id, state );
	//}


	///// @brief	Register a state change to happen on an event ID after internal OnState
	/////			code of the state is executed and returns a 0 results transition.
	/////
	/////	@param	id		The event id.
	///// @param	state	The state to transition to on event id.
	//void RegisterEventLateTransition( unsigned int id, mr_state* state )
	//{
	//	this->AssertNotRegistered( this->GetEventLateTransition( id ), FL );
	//	m_evLateTransitions.push_back( id, state );
	//}


	///// @brief	Register a state change to happen as a result of internally returned ID from
	/////			the body of the OnState code.
	/////
	/////	@param	id		The event id.
	///// @param	state	The state to transition to on the result id.
	//void RegisterResultTransition( unsigned int id, mr_state* state )
	//{
	//	this->AssertNotRegistered( this->GetResultsTransition( id ), FL );
	//	m_rTransitions.push_back( id, state );
	//}


	/// @brief	Pulse the state for it to execute its code.
	///
	/// @param	Tevent	The event to push at the state.
	///
	/// @return NULL if no state change required, otherwise the new state.
	virtual mr_state* PulseState( const T& Tevent )
	{
		//// Check for pre-emptive, then results, then default post event transitions.
		//mr_state* nextState = this->GetEventEarlyTransition( Tevent.m_id );
		//if (nextState == NULL)
		//{
		//	nextState = this->GetResultsTransition( this->OnState( Tevent ) );
		//	if (nextState == NULL)
		//	{
		//		return this->GetEventLateTransition( Tevent.m_id );
		//	}
		//}
		//return nextState;

		return NULL;
	}

protected:

	virtual void OnEntry()
	{
	}


	virtual unsigned int OnState( const T& event ) = 0;


	virtual void OnExit()
	{
	}

private:

	//typedef std::vector<mr_transitionInfo<T> >		zMR_TRANSITION_VEC;	///< Transition vector.
	typedef typename zMR_TRANSITION_VEC::iterator	zMR_TRANSITION_IT;	///< Transition vector iterator.
	zMR_TRANSITION_VEC	zm_evEarlyTransitions;	///< possible transitions before any state code execution.
	zMR_TRANSITION_VEC	zm_evLateTransitions;	///< possible transitions after state code execution.
	zMR_TRANSITION_VEC	zm_rTransitions;			///< possible transitions from internal code execution.


	/// @brief	Retrieves the next state based on an id.
	///
	/// @param	id	The id of the event or result.
	///
	/// @return	The next state to transition to or NULL if no matching id.
	mr_transitionInfo<T> zGetTransition( zMR_TRANSITION_VEC& vec, int id )
	{
		zMR_TRANSITION_ITERATOR it = std::find_if( vec.begin(), vec.end(), zfindTransition<T>( id ) );
		if (it == vec.end())
		{
			return *it;
		}
		return mr_transitionInfo<T>( id, NO_CHANGE );
	}


	/// @brief	Retrieves the pre-emptive event next state based on an event id.
	///
	/// @param	id	The id of the event.
	///
	/// @return	The next state to transition to or NULL if no matching id.
	mr_transitionInfo<T> zGetEventEarlyTransition( int id )
	{
		return this->zGetTransition( zm_evEarlyTransitions, id );
	}


	/// @brief	Retrieves the post code next state based on an event id.
	///
	/// @param	id	The id of the event.
	///
	/// @return	The next state to transition to or NULL if no matching id.
	mr_transitionInfo<T> zGetEventLateTransition( int id )
	{
		return this->zGetTransition( m_evLateTransitions, id );
	}


	/// @brief	Retrieves the next state based on a result id.
	///
	/// @param	id	The id of the result.
	///
	/// @return	The next state to transition to or NULL if no matching id.
	mr_transitionInfo<T> zGetResultsTransition( int id )
	{
		return this->zGetTransition( m_rTransitions, id );
	}

///////////////////////////////////////////////////////////////////



	//typedef std::pair<unsigned int,mr_state<T >* > MR_TRANSITION_PAIR;	///< Transition pair.
	//typedef std::vector<MR_TRANSITION_PAIR >	   MR_TRANSITION_VEC;	///< Transition vector.
	//typedef typename std::vector<MR_TRANSITION_PAIR >::iterator	MR_TRANSITION_ITERATOR; ///< Transition iterator.

	unsigned int		m_id;					///< State ID.
	//MR_TRANSITION_VEC	m_evEarlyTransitions;	///< possible transitions before any state code execution.
	//MR_TRANSITION_VEC	m_evLateTransitions;	///< possible transitions after state code execution.
	//MR_TRANSITION_VEC	m_rTransitions;			///< possible transitions from internal code execution.

	
//	/// @brief	Retrieves the next state based on an id.
//	///
//	/// @param	id	The id of the event or result.
//	///
//	/// @return	The next state to transition to or NULL if no matching id.
//	mr_state* GetTransition( MR_TRANSITION_VEC& vec, int id )
//	{
//		MR_TRANSITION_ITERATOR it = std::find_if( vec.begin(), vec.end(), findTransition<T>( id ) );
//		return ( it == vec.end() ? NULL : it->second );
//	}
//
//
//	/// @brief	Retrieves the pre-emptive event next state based on an event id.
//	///
//	/// @param	id	The id of the event.
//	///
//	/// @return	The next state to transition to or NULL if no matching id.
//	mr_state* GetEventEarlyTransition( int id )
//	{
//		return this->GetTransition( m_evEarlyTransitions, id );
//	}
//
//
//	/// @brief	Retrieves the post code next state based on an event id.
//	///
//	/// @param	id	The id of the event.
//	///
//	/// @return	The next state to transition to or NULL if no matching id.
//	mr_state* GetEventLateTransition( int id )
//	{
//		return this->GetTransition( m_evLateTransitions, id );
//	}
//
//
//	/// @brief	Retrieves the next state based on a result id.
//	///
//	/// @param	id	The id of the result.
//	///
//	/// @return	The next state to transition to or NULL if no matching id.
//	mr_state* GetResultsTransition( int id )
//	{
//		return this->GetTransition( m_rTransitions, id );
//	}


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

//
//
////----------------------------------------------------------
///// @Functor to find if the event is already registered.
//template<class T>
//struct findTransition
//{
//	findTransition( unsigned int target ) : m_target( target ) {}
//
//	bool operator ()( const std::pair<unsigned int,mr_state<T>*>& tp ) const
//	{
//		return tp.first == m_target;
//	}
//	unsigned int m_target; ///< Target transition identifier.
//};



///////////////////////////////////////////////////////////////////////

//----------------------------------------------------------
/// @Functor to find if the event is already registered.
template<class T>
struct zfindTransition
{
	zfindTransition( unsigned int target ) : m_target( target ) {}

	bool operator ()( const mr_transitionInfo<T>& ti ) const
	{
		return ti.m_id == m_target;
	}
	unsigned int m_target; ///< Target transition identifier.
};





} // end namespace.

#endif