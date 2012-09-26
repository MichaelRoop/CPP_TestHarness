///--------------------------------------------------------------------------------------
/// @file	mr_sharedPtr.h
/// @brief	Reference counted pointer holder.
///
/// @author		Michael Roop
/// @date		2010
/// @version	1.0
///
/// @todo	Thread locking?
///
/// Copyright 2010 Michael Roop
///--------------------------------------------------------------------------------------
#if !defined(MR_SHARED_PTR_H) 
#define MR_SHARED_PTR_H

#include "MrTestUtilsDefine.h"
#include <assert.h>


namespace mr_utils {

template<class T>
class SharedPtr {
public:

	SharedPtr() : m_ptr(NULL), m_count(NULL) {
	}


	SharedPtr(T* ptr) : m_ptr(NULL), m_count(NULL) {
		this->AssignPtr(ptr);
	}

	
	SharedPtr(const SharedPtr& sp) : m_ptr(NULL), m_count(NULL) {
		this->AssignSharedPtr(sp);
	}


	~SharedPtr() {
		this->Decrement();
	}


	SharedPtr& operator = (const SharedPtr& sp) {
		if (&sp != this) {
			this->AssignSharedPtr( sp );
		}
		return *this;
	}


	SharedPtr& operator = (T* ptr) {
		this->AssignPtr(ptr);
		return *this;
	}


	T* operator -> () {
		return this->getPtr();
	}


	T& operator *() {
		return this->getRef();
	}


	T* getPtr() {
		assert( m_ptr );
		return m_ptr;
	}


	T& getRef() {
		return *(this->getPtr());
	}


	unsigned getCount() const {
		if (m_count != NULL) {
			return *m_count;
		}
		return 0;
	}

	
	bool isValid() const {
		return m_ptr != NULL;
	}


	void reset() {
		this->AssignPtr( NULL );
	}


private:
	T*			m_ptr;
	unsigned*	m_count;


	void AssignPtr(T* ptr) {
		this->Decrement();
		if (ptr != NULL) {
			m_count = new unsigned();
			*m_count = 1;
		}
		m_ptr = ptr;
	}


	void AssignSharedPtr(const SharedPtr& sp) {
		this->Decrement();
		if (sp.m_count != NULL) {
			++(*sp.m_count);
		}
		m_count = sp.m_count;
		m_ptr	= sp.m_ptr;
	}


	void Decrement() {
		if (m_count != NULL) {
			--(*m_count);
			if (*m_count == 0) {
				delete m_ptr;
				m_ptr = NULL;
				delete m_count;
				m_count = NULL;
			}
		}
	}


};

} // End namespace

#endif
