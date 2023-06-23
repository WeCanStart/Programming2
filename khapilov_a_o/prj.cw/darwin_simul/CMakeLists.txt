add_subdirectory(examples)
add_subdirectory(test)

add_library(darwinsimul INTERFACE include/darwin_simul/darwin_simul.hpp)
set_property(TARGET darwinsimul PROPERTY CXX_STANDARD 20)
target_include_directories(darwinsimul PUBLIC INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include DESTINATION .)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doc_doxygen/ DESTINATION ./doc)

option(BUILD_DOC "Build documentation" ON)

set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/./doc/Doxyfile.in)
set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

find_package(Doxygen REQUIRED)

configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

add_custom_target(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        VERBATIM
)
