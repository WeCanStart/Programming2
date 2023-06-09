add_subdirectory(src/pl_he_pr_simul)

add_executable(generator generator.cpp)
target_link_libraries(generator plHePrSimul)

add_executable(example example.cpp)
target_link_libraries(example plHePrSimul sfml-window sfml-graphics)
