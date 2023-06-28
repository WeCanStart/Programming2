cmake_minimum_required(VERSION 3.18)   

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(CMAKE_VERBOSE_MAKEFILE True)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE} DESTINATION .)

project(darwinSimul)

add_subdirectory(examples)
add_subdirectory(test)

add_library(darwinSimul INTERFACE include/darwin_simul/darwin_simul.hpp)
set_property(TARGET darwinSimul PROPERTY CXX_STANDARD 20)
target_include_directories(darwinSimul PUBLIC INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

install(
    TARGETS darwinSimul
    LIBRARY DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc_doxygen/ DESTINATION ./doc COMPONENT test)
install(FILES ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/sfml-graphics-2.dll
              ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/sfml-window-2.dll
              ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/sfml-system-2.dll
              ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/freetype.dll
              ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/libpng16.dll
              ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/bz2.dll
              ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/zlib1.dll
              ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/brotlidec.dll
              ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/brotlicommon.dll
        DESTINATION ./bin COMPONENT test)

option(BUILD_DOC "Build documentation" ON)

find_package(Doxygen)

if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/./doc/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
