cmake_minimum_required(VERSION 3.28)
project(MidiKeyboard LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
libremidi
GIT_REPOSITORY https://github.com/celtera/libremidi
GIT_TAG        v4.5.0
)
FetchContent_MakeAvailable(libremidi)

include_directories(include)

add_executable(midi-keyboard 
    src/main.cpp
    src/midi_out.cpp
    src/midi.cpp
    src/arpeggiator.cpp)
target_link_libraries(midi-keyboard PRIVATE sfml-graphics libremidi)
target_compile_features(midi-keyboard PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET midi-keyboard
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:midi-keyboard>
        VERBATIM)
endif()
