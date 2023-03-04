add_executable(arrayD_test arrayD_test.cpp)
target_link_libraries(arrayD_test arrayD doctest::doctest)
add_test(NAME arrayD_test COMMAND arrayD_test)

