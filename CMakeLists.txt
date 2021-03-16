cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(simple_model)

# set(CUDA_NVRTC_LIB "/usr/local/cuda-11.1/include/nvrtc.h")
find_package( Torch REQUIRED )
# find_package(TorchVision REQUIRED)

add_executable(simple_model model.cpp)
target_link_libraries(simple_model "${TORCH_LIBRARIES}")
#target_link_libraries(simple_model PUBLIC TorchVision::TorchVision)
#set_property(TARGET simple_model PROPERTY CUDA_ARCHITECTURES 60 61 62 70 72 75 80 86)
set_property(TARGET simple_model PROPERTY CXX_STANDARD 14)
