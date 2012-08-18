// ExperimentThrowCatch.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <exception>

class xecept : public std::exception {
	xecept() : exception("woof") {
	}
};


/*
#define _DOES_THROW(_fixture_, _exception_, _logic_) \
	try {									\
		(_logic_);							\
		_ARE_EQUAL(_fixture_, 1, 2);		\
	}										\
	catch (const (_exception_)& e) {			\
		prinf("caught exception");			\
	}										\
*/



/*
	try {									\
		(_logic_);							\
		std::cout << "Logic block" << std::endl;	\
	}										\
	catch (const (_exception_)& e) {			\
		prinf("caught exception");			\
	}										\
*/

#define _WRAP_BLOCK( _logic_)			 \
		(_logic_);							\


#define _WRAP_TRY_BLOCK( _logic_)			 \
	try {	\
		(_logic_);							\
			std::cout << "No throw" << std::endl; \
		}	\
		catch (...) {  \
			std::cout << "Caught something" << std::endl; \
		}  \


#define _WRAP_TRY_BLOCK2( _logic_, _exType_)						\
	try {															\
		(_logic_);													\
			std::cout << "No throw" << std::endl;					\
		}															\
		catch (const _exType_&) {									\
			std::cout << "Caught expected exception type" << std::endl;	\
		}															\
		catch (...) {												\
		std::cout << "Caught exception other than expected '" << (#_exType_) << "' exception type"  << std::endl;		\
		}															\




//		std::cout << "Logic block" << std::endl;	\

static void ThrowMethod();

static void TestWrapDelegate();
static void TestThrowCatch();
static void TestThrowCatch2();
static void TestThrowCatch3();
static void TestThrowCatchEx();
static void TestThrowCatchEx2();

typedef void (func) (void);
typedef void (*  func_ptr) (void);

#define DO_FUNC(_func_ptr_) \
	static_cast<func_ptr>(_func_ptr_)(); \

//static void ExecFuncPtrTest() {
//	std::cout << "ExecFuncPtrTest" << std::endl;
//
//	DO_FUNC((std::cout << "ExecFuncPtrTest" << std::endl));
//}

static void SampleFunc() {
	std::cout << "sample statement 1" << std::endl;
	std::cout << "sample statement 2" << std::endl;
}
static void ExecFuncPtrTest() {
	std::cout << "ExecFuncPtrTest" << std::endl;

	DO_FUNC(SampleFunc);
}

//static void ExecFuncPtrTest2() {
//	std::cout << "ExecFuncPtrTest" << std::endl;
//
//	DO_FUNC(*(new func_ptr{
//		std::cout << "sample statement 1" << std::endl;
//		std::cout << "sample statement 2" << std::endl;})
//	);
//}

int main(int argc, char* argv[])
{
	ExecFuncPtrTest();


	TestWrapDelegate();
	TestThrowCatch();
	TestThrowCatch2();
	TestThrowCatch3();
	TestThrowCatchEx();
	TestThrowCatchEx2();

	return 0;
}


static void TestWrapDelegate() {
	_WRAP_BLOCK((
		std::cout << "blah" << std::endl))

}

static void TestThrowCatch() {
	_WRAP_TRY_BLOCK((
		std::cout << "blah" << std::endl))
}

static void TestThrowCatch2() {
	_WRAP_TRY_BLOCK((
		throw std::exception("Blah exception")))
}

static void ThrowMethod() {
	std::cout << "throw method" << std::endl;
	throw std::exception("Blah exception");
}

static void TestThrowCatch3() {
	_WRAP_TRY_BLOCK((
		ThrowMethod()))
}

static void TestThrowCatchEx() {
	std::cout << "Catch expected exception type" << std::endl;
	_WRAP_TRY_BLOCK2((ThrowMethod()), std::exception)
}

static void TestThrowCatchEx2() {
	std::cout << "Catch non expected Expect type" << std::endl;
	_WRAP_TRY_BLOCK2(ThrowMethod(), xecept)
}


