
// Queued Event Data tests are THR_2_2_n 


#include "CppTestMacros.h"
#include "mr_dataEvent.h"
#include "mr_queuedDataEvent.h"
#include "CppTestCompareFunctions.h"

#include <algorithm>


struct pushDataEventsFunctor
{
	pushDataEventsFunctor( mr_threads::mr_queuedDataEvent<mr_utils::mr_string>& ev )
		: m_events( ev ) {}

	void operator () ( const mr_utils::mr_string& str )
	{
		m_events.Signal( str );
	}
	mr_threads::mr_queuedDataEvent<mr_utils::mr_string>& m_events;


private:
	/// @brief	Protected assignement operator.
	pushDataEventsFunctor& operator = ( const pushDataEventsFunctor& ) { return *this; }

};


/// @brief	Base test case.
class QueuedDataEventTests : public CppTest::Fixture
{
public:
	QueuedDataEventTests() : CppTest::Fixture( _L_("QueuedDataEventTests"), _L_("") ) {
		_ADD_TEST_FIXTURE_(this);
		_FIXTURE_SETUP_(this, &QueuedDataEventTests::FixtureSetup); 
	}

	void FixtureSetup()
	{
		m_data.push_back( mr_utils::mr_string( L("this is") ) );
		m_data.push_back( mr_utils::mr_string( L("a couple") ) );
		m_data.push_back( mr_utils::mr_string( L("of data") ) );
		m_data.push_back( mr_utils::mr_string( L("objects for") ) );
		m_data.push_back( mr_utils::mr_string( L("queued events") ) );
		std::for_each( m_data.begin(), m_data.end(), pushDataEventsFunctor( m_events ) );
	}


	virtual bool GetEventData( mr_utils::mr_string& /*str*/ )
	{
		return false;
	}


	bool test()
	{
		if (CppTest::CompareEqual( m_data.size(), m_events.QueuedCount(), this->CurrentTestCase().MsgBuffer)) {
			std::vector<mr_utils::mr_string> target;
			for (unsigned int i = 0; i < m_data.size(); ++i) {
				mr_utils::mr_string s;
				
				if (!CppTest::CompareEqual(this->GetEventData(s), true, this->CurrentTestCase().MsgBuffer, L("Did not get data"))) {
					return false;
				}
				target.push_back( s );
			}

			// check for empty queue.
			if (CppTest::CompareEqual( (unsigned)0, m_events.QueuedCount(), this->CurrentTestCase().MsgBuffer, L("Queue not empty"))) {
				return CppTest::VerbCompareVecEqual( FL, m_data, target, this->CurrentTestCase().VerboseBuffer, L("Vectors not equal"));
			}
		}
		return false;
	}


//_DECL_TEST_( _mr_queuedDataEventTest1, queuedDataEventTestBase)
//	bool test()	
//	{ 
//		return mr_test::CompareEqual( m_data.size(), m_events.QueuedCount(), this->getMsgBuffer());
//	}
//_REG_TEST_( THR_2_2_1, instTHR_2_2_1, _mr_queuedDataEventTest1, L("Matched queued count") )
//
//
//_DECL_TEST_( _mr_queuedDataEventTest2, queuedDataEventTestBase)
//	bool GetEventData( mr_utils::mr_string& str )
//	{
//		m_events.Wait( str );
//		return true;
//	}
//_REG_TEST_( THR_2_2_2, instTHR_2_2_2, _mr_queuedDataEventTest2, L("Matched queued entries-Wait") )
//
//
//_DECL_TEST_( _mr_queuedDataEventTest3, queuedDataEventTestBase)
//	bool GetEventData( mr_utils::mr_string& str )
//	{
//		return m_events.IsSignaled( str );
//	}
//_REG_TEST_( THR_2_2_3, instTHR_2_2_3, _mr_queuedDataEventTest3, L("Matched queued entries- IsSelected") )



protected:
	std::vector<mr_utils::mr_string>					m_data;
	mr_threads::mr_queuedDataEvent<mr_utils::mr_string>	m_events;

};
_REGISTER_FIXTURE_(QueuedDataEventTests);


//_DECL_TEST_( _mr_queuedDataEventTest1, queuedDataEventTestBase)
//	bool test()	
//	{ 
//		return mr_test::CompareEqual( m_data.size(), m_events.QueuedCount(), this->getMsgBuffer());
//	}
//_REG_TEST_( THR_2_2_1, instTHR_2_2_1, _mr_queuedDataEventTest1, L("Matched queued count") )
//
//
//_DECL_TEST_( _mr_queuedDataEventTest2, queuedDataEventTestBase)
//	bool GetEventData( mr_utils::mr_string& str )
//	{
//		m_events.Wait( str );
//		return true;
//	}
//_REG_TEST_( THR_2_2_2, instTHR_2_2_2, _mr_queuedDataEventTest2, L("Matched queued entries-Wait") )
//
//
//_DECL_TEST_( _mr_queuedDataEventTest3, queuedDataEventTestBase)
//	bool GetEventData( mr_utils::mr_string& str )
//	{
//		return m_events.IsSignaled( str );
//	}
//_REG_TEST_( THR_2_2_3, instTHR_2_2_3, _mr_queuedDataEventTest3, L("Matched queued entries- IsSelected") )
//


