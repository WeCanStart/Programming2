add_subdirectory(src/pl_he_pr_simul)

add_executable(generator generator.cpp)
target_link_libraries(generator plHePrSimul)

find_package(SFML COMPONENTS window graphics system REQUIRED)

add_executable(example example.cpp)
target_link_libraries(example plHePrSimul sfml-window sfml-graphics)

install(TARGETS generator example DESTINATION bin COMPONENT test)
