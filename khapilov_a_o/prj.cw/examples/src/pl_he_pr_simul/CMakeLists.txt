add_library(plHePrSimul INTERFACE include/pl_he_pr_simul/pl_he_pr_simul.hpp)
target_link_libraries(plHePrSimul INTERFACE darwinSimul)
set_property(TARGET plHePrSimul PROPERTY CXX_STANDARD 20)
target_include_directories(plHePrSimul PUBLIC INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

install(
    TARGETS plHePrSimul
    LIBRARY DESTINATION lib
)
