If (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
   Set(
       CMAKE_CXX_FLAGS_DEBUG
       "${CMAKE_CXX_FLAGS_DEBUG} -std=c++1z -O0 -fexceptions -fmodules \
       -fcxx-modules -Werror -Wall -Wfatal-errors -Wextra -fdiagnostics-color=always"
    )
   Set(
       CMAKE_CXX_FLAGS_RELEASE
       "${CMAKE_CXX_FLAGS_RELEASE} -std=c++1z -O3 -fmodules -fcxx-modules \
       -Werror -Wall -Wfatal-errors -Wextra -fdiagnostics-color=always"
    )
ElseIf (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    Set(
       CMAKE_CXX_FLAGS_DEBUG
       "${CMAKE_CXX_FLAGS_DEBUG} -std=c++1z -O0 -fexceptions -g -pedantic \ 
       -fconcepts -Wall -Werror -Wfatal-errors -Wextra -fdiagnostics-color=always"
    )
    Set(
       CMAKE_CXX_FLAGS_RELEASE 
       "${CMAKE_CXX_FLAGS_RELEASE} -std=c++1z -O0 -g -pedantic -fconcepts \
        -Wall -Werror -Wfatal-errors -Wextra -fdiagnostics-color=always"
    )
ElseIf (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    Add_Definitions("-DGTEST_LANG_CXX11=1")
    Add_Definitions(-DUNICODE -D_UNICODE)
    Set(
        CMAKE_CXX_FLAGS_DEBUG 
        "${CMAKE_CXX_FLAGS_DEBUG} /std:c++latest /Od /Zi /W4 /EHsc /MDd"
    )
    Set(
        CMAKE_CXX_FLAGS_RELEASE
        "${CMAKE_CXX_FLAGS_RELEASE} /std:c++latest /Ox /W4 /EHsc"
    )
Else ()
    MESSAGE(FATAL_ERROR "Not supported compiler")
EndIf ()
