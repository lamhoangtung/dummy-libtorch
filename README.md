# Dummy libtorch model

This repo is used to reproduce a bug in libtorch 1.8.0

How to use it

```bash
sh download_libtorch.sh
sh build.sh
```

Expected output:
```console
-- The C compiler identification is GNU 9.3.0
-- The CXX compiler identification is GNU 9.3.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Looking for pthread.h
-- Looking for pthread.h - found
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Failed
-- Looking for pthread_create in pthreads
-- Looking for pthread_create in pthreads - not found
-- Looking for pthread_create in pthread
-- Looking for pthread_create in pthread - found
-- Found Threads: TRUE
-- Found CUDA: /usr/local/cuda-11.1 (found version "11.1")
-- Caffe2: CUDA detected: 11.1
-- Caffe2: CUDA nvcc is: /usr/local/cuda-11.1/bin/nvcc
-- Caffe2: CUDA toolkit directory: /usr/local/cuda-11.1
-- Caffe2: Header version is: 11.1
-- Found CUDNN: /usr/local/cuda-11.1/lib64/libcudnn.so
-- Found cuDNN: v8.1.1  (include: /usr/local/cuda-11.1/include, library: /usr/local/cuda-11.1/lib64/libcudnn.so)
CMake Warning at libtorch/share/cmake/Caffe2/public/cuda.cmake:198 (message):
  Failed to compute shorthash for libnvrtc.so
Call Stack (most recent call first):
  libtorch/share/cmake/Caffe2/Caffe2Config.cmake:88 (include)
  libtorch/share/cmake/Torch/TorchConfig.cmake:68 (find_package)
  CMakeLists.txt:4 (find_package)


-- Autodetected CUDA architecture(s):  8.6 6.1
-- Added CUDA NVCC flags for: -gencode;arch=compute_86,code=sm_86;-gencode;arch=compute_61,code=sm_61
-- Found Torch: /home/techainer/linus/dummy-libtorch/libtorch/lib/libtorch.so
-- Configuring done
-- Generating done
-- Build files have been written to: /home/techainer/linus/dummy-libtorch/build
Scanning dependencies of target simple_model
[ 50%] Building CXX object CMakeFiles/simple_model.dir/model.cpp.o
[100%] Linking CXX executable simple_model
[100%] Built target simple_model
```