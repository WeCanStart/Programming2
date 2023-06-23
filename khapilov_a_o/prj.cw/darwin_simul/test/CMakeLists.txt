find_package(doctest REQUIRED)

add_executable(test test.cpp)
target_link_libraries(test plHePrSimul doctest::doctest)
add_test(NAME test COMMAND test)

install(DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE} DESTINATION .)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../test DESTINATION ./bin.rel)