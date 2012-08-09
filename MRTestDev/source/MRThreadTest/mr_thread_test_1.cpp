
#include "mr_case.h"
#include "mr_testMacros.h"
#include "mr_threadObj.h"
#include "mr_lockedWriteOut.h"
#include "mr_threadFunctions.h"


class SleepingThread : public mr_threads::mr_threadObj
{
public:
	SleepingThread( int msSleep = 0 ) : mr_threads::mr_threadObj(), m_sleep( msSleep )
	{
	}

protected:

	virtual void Run()
	{
		for (int i = 0; i < 8; ++i )
		{
			this->threadInfo();
			this->Sleep( m_sleep );
		}
	}

private:
	int m_sleep; ///< Sleep duration.

	void threadInfo()
	{
		mr_utils::mr_stringstream ss;
		ss << L("Thread Id=") << this->Id() << L(", Sleep time=") << m_sleep ;
		mr_threads::LockedWriteLineToConsole( ss );
	}
};
//-----------------------------------------------------------



class ThreadLogger
{
public:

	ThreadLogger( std::vector<mr_utils::mr_string>& vs ) :
	  m_strings( vs )
	  {
	  }


private:

	std::vector<mr_utils::mr_string>&	m_strings;
	mr_threads::mr_mutex				m_mutex;

	ThreadLogger& operator = ( const ThreadLogger& ) { return *this; }

};




class NoSleepThread : public mr_threads::mr_threadObj
{
public:
	NoSleepThread( int priority ) : mr_threads::mr_threadObj( priority )
	{
	}

protected:

	virtual void Run()
	{
		for (int i = 0; i < 15; ++i )
		{
			//long x = 0;
			//for (int j=0; j < 10000; ++j)
			//{
			//	x += x + j;
			//}
			//x = 0;

			this->threadInfo();
		}
	}

private:
	int m_sleep; ///< Sleep duration.

	void threadInfo()
	{
		mr_utils::mr_stringstream ss;
		ss << L("Thread Id=") << this->Id() << L(", Priority=") << this->GetCurrentPriority() << std::endl;
		mr_cout << ss.str();



		//ss << L("Thread Id=") << this->Id() << L(", Priority=") << this->GetCurrentPriority() ;
		//mr_threads::LockedWriteLineToConsole( ss );
	}
};
//-----------------------------------------------------------



/// @brief	Base test case.
class baseThreadTest : public mr_test::testCase
{
public:
	baseThreadTest(  const mr_utils::mr_string& name, const mr_utils::mr_string& desc )
		: mr_test::testCase( name, desc ),
		m_th1( 111 ),
		m_th2( 225 )
	{
	}


	void RunSequence()	
	{ 
		mr_threads::LockedWriteLineToConsole( L( "Before Starts" ) );

		m_th1.Start();
		m_th2.Start();

		mr_threads::LockedWriteLineToConsole( L( "Before Joins" ) );

		m_th1.Join();
		m_th2.Join();

		mr_threads::LockedWriteLineToConsole( L( "After Joins" ) );
	}

protected:

	SleepingThread m_th1;
	SleepingThread m_th2;
};


_DECL_TEST_( _mr_threadTEst1, baseThreadTest)
	bool test()	
	{ 
		this->RunSequence();
		return true;
	}
_REG_TEST_( THR_1_1, instTHR_1_1, _mr_threadTEst1, L("Thread interleave two threads") )


_DECL_TEST_( _mr_threadTEst2, baseThreadTest)
	bool test()	
	{ 
		mr_threads::LockedWriteLineToConsole( L( "Before First Start" ) );
		this->RunSequence();
		mr_threads::LockedWriteLineToConsole( L( "Before Second Start" ) );
		this->RunSequence();
		return true;
	}
_REG_TEST_( THR_1_2, instTHR_1_2, _mr_threadTEst2, L("Thread start twice") )



_DECL_TEST_( _mr_threadTEst3, baseThreadTest)
	bool test()	
	{ 
		NoSleepThread t1( MR_DEFAULT_THREAD_PRIORITY + 15 );
		//NoSleepThread t2;
		//NoSleepThread t3;
		//NoSleepThread t4;
		//NoSleepThread t5;
		//NoSleepThread t6;
		NoSleepThread t7( MR_DEFAULT_THREAD_PRIORITY - 2 );

		//t1.SetNewPriority( MR_DEFAULT_THREAD_PRIORITY + 15 );
		//t2.SetNewPriority( MR_DEFAULT_THREAD_PRIORITY + 2 );
		//t3.SetNewPriority( MR_DEFAULT_THREAD_PRIORITY + 1 );
		//t4.SetNewPriority( MR_DEFAULT_THREAD_PRIORITY );
		//t5.SetNewPriority( MR_DEFAULT_THREAD_PRIORITY - 1 );
		//t6.SetNewPriority( MR_DEFAULT_THREAD_PRIORITY - 2 );
		//t7.SetNewPriority( MR_DEFAULT_THREAD_PRIORITY - 15 );

		t1.Start();

		//mr_threads::MRSleep( 1 );

		//t2.Start();
		//t3.Start();
		//t4.Start();
		//t5.Start();
		//t6.Start();

		t7.Start();


		t1.Join();
		//t2.Join();
		//t3.Join();
		//t4.Join();
		//t5.Join();
		//t6.Join();
		t7.Join();

		//mr_threads::LockedWriteLineToConsole( L( "After Joins" ) );

		//this->RunSequence();
		return true;
	}
_REG_TEST_( THR_1_3, instTHR_1_3, _mr_threadTEst3, L("Thread First higher priority") )












