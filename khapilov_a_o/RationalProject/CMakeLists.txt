# CMakeList.txt: проект CMake для Rational; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project (RationalProject)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

include_directories(.)

add_subdirectory("rational")

add_executable(rational.doctest rational.doctest.cpp)
set_property(TARGET rational.doctest PROPERTY CXX_STANDARD 20)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT rational.doctest)
target_link_libraries(rational.doctest rational)
