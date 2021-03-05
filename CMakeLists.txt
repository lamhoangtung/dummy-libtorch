cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(simple_model)

find_package( Torch REQUIRED )

add_executable(simple_model model.cpp)
target_link_libraries(simple_model "${TORCH_LIBRARIES}")
set_property(TARGET simple_model PROPERTY CXX_STANDARD 14)