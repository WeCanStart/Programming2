find_package(doctest REQUIRED)

add_executable(test test.cpp)
target_link_libraries(test plHePrSimul doctest::doctest)
add_test(NAME test COMMAND test)

install(TARGETS test DESTINATION bin COMPONENT test)