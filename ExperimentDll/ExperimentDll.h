// ExperimentDll.h

#pragma once

#include <iostream>

using namespace System;



#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif

__declspec(dllexport) void __cdecl  Func1() {
	std::cout << "Executed Func1" << std::endl;
}

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif

__declspec(dllexport) void __cdecl  Func2() {
	std::cout << "Executed Func2" << std::endl;
}

#ifdef __cplusplus
}
#endif


 void  Func3() {
	std::cout << "Executed Func3" << std::endl;
}

	//void Func1() {
	//	std::cout << "Executed Func1" << std::endl;
	//}



namespace ExperimentDll {
	public ref class Class1
	{
		// TODO: Add your methods for this class here.
	};
}
