add_library(figure figure.cpp include/figure/figure.hpp)
set_property(TARGET figure PROPERTY CXX_STANDARD 20)
target_include_directories(figure PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS figure)
