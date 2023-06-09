find_package(SFML COMPONENTS window graphics system REQUIRED)
find_package(doctest REQUIRED)

add_subdirectory(examples)
add_subdirectory(test)

add_library(darwinsimul INTERFACE include/darwin_simul/darwin_simul.hpp)
set_property(TARGET darwinsimul PROPERTY CXX_STANDARD 20)
target_include_directories(darwinsimul PUBLIC INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

install(TARGETS darwinsimul)
