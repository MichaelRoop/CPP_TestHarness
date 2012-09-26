
//// TODO - find out why these have to be included in the header for the test cases to register
#include "TestList.h"

// THis is the method for self registering the test cases. Used by those OSs that do not yet have 
// DLL header parsing implemented
NON_PARSED_HEADER_REGISTER_BLOCK_START
    REGISTER_FIXTURE_MAIN(TokenizerTests1);
    REGISTER_FIXTURE_MAIN(TokenizerTests2);
    REGISTER_FIXTURE_MAIN(UtilStrTrimTests);
    REGISTER_FIXTURE_MAIN(MrTestMacroTests);
NON_PARSED_HEADER_REGISTER_BLOCK_END


