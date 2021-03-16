# Dummy libtorch model

This repo is used to reproduce a [bug #54053](https://github.com/pytorch/pytorch/issues/54053) in libtorch 1.8.0

To use this, setup everything on a machine that had a GPU with compute capability 6.1 like the GTX 1080Ti. Please install CUDA 11.1 or virtualize CUDA 11.1 inside the docker image `nvidia/cuda:11.1.1-cudnn8-devel-ubuntu20.04`:
```bash
# Setup related dependencies
sudo apt update
sudo apt install unzip cmake git python3 python3-dev python3-pip wget

# Clone the repo and checkout related branch
git clone https://github.com/lamhoangtung/dummy-libtorch
cd dummy-libtorch
git checkout no_execution_kernel_bug

# Download libtorch and build the program
sh download_libtorch.sh
sh build.sh
```

Expected output:
```console
root@e43fcbbb4f19:/dummy-libtorch# ./build.sh
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
-- Found CUDA: /usr/local/cuda (found version "11.1")
-- Caffe2: CUDA detected: 11.1
-- Caffe2: CUDA nvcc is: /usr/local/cuda/bin/nvcc
-- Caffe2: CUDA toolkit directory: /usr/local/cuda
-- Caffe2: Header version is: 11.1
-- Found CUDNN: /usr/lib/x86_64-linux-gnu/libcudnn.so
-- Found cuDNN: v8.0.5  (include: /usr/include, library: /usr/lib/x86_64-linux-gnu/libcudnn.so)
CMake Warning at libtorch/share/cmake/Caffe2/public/cuda.cmake:198 (message):
  Failed to compute shorthash for libnvrtc.so
Call Stack (most recent call first):
  libtorch/share/cmake/Caffe2/Caffe2Config.cmake:88 (include)
  libtorch/share/cmake/Torch/TorchConfig.cmake:68 (find_package)
  CMakeLists.txt:5 (find_package)


-- Autodetected CUDA architecture(s):  6.1
-- Added CUDA NVCC flags for: -gencode;arch=compute_61,code=sm_61
-- Found Torch: /dummy-libtorch/libtorch/lib/libtorch.so
-- Configuring done
-- Generating done
-- Build files have been written to: /dummy-libtorch/build
Scanning dependencies of target simple_model
[ 50%] Building CXX object CMakeFiles/simple_model.dir/model.cpp.o
[100%] Linking CXX executable simple_model
[100%] Built target simple_model
```

And run the binary:
```console
root@e43fcbbb4f19:/dummy-libtorch# ./build/simple_model python/test.pt
Loading model python/test.pt
Loaded model python/test.pt
terminate called after throwing an instance of 'c10::Error'
  what():  CUDA error: no kernel image is available for execution on the device
Exception raised from distribution_nullary_kernel at /pytorch/aten/src/ATen/native/cuda/DistributionTemplates.h:158 (most recent call first):
frame #0: c10::Error::Error(c10::SourceLocation, std::string) + 0x42 (0x7f5e8b9c02f2 in /dummy-libtorch/libtorch/lib/libc10.so)
frame #1: c10::detail::torchCheckFail(char const*, char const*, unsigned int, std::string const&) + 0x5b (0x7f5e8b9bd67b in /dummy-libtorch/libtorch/lib/libc10.so)
frame #2: void at::native::(anonymous namespace)::distribution_nullary_kernel<float, float, 4, at::CUDAGeneratorImpl*, __nv_dl_wrapper_t<__nv_dl_tag<void (*)(at::TensorIterator&, at::CUDAGeneratorImpl*, __nv_dl_wrapper_t<__nv_dl_tag<void (*)(at::Tensor&, double, double, at::CUDAGeneratorImpl*), &(void at::native::templates::cuda::normal_kernel<at::CUDAGeneratorImpl*>(at::Tensor&, double, double, at::CUDAGeneratorImpl*)), 2u>, float, float>), &(void at::native::templates::cuda::normal_and_transform<float, float, 4ul, at::CUDAGeneratorImpl*, __nv_dl_wrapper_t<__nv_dl_tag<void (*)(at::Tensor&, double, double, at::CUDAGeneratorImpl*), &(void at::native::templates::cuda::normal_kernel<at::CUDAGeneratorImpl*>(at::Tensor&, double, double, at::CUDAGeneratorImpl*)), 2u>, float, float> >(at::TensorIterator&, at::CUDAGeneratorImpl*, __nv_dl_wrapper_t<__nv_dl_tag<void (*)(at::Tensor&, double, double, at::CUDAGeneratorImpl*), &(void at::native::templates::cuda::normal_kernel<at::CUDAGeneratorImpl*>(at::Tensor&, double, double, at::CUDAGeneratorImpl*)), 2u>, float, float>)), 2u>>, __nv_dl_wrapper_t<__nv_dl_tag<void (*)(at::Tensor&, double, double, at::CUDAGeneratorImpl*), &(void at::native::templates::cuda::normal_kernel<at::CUDAGeneratorImpl*>(at::Tensor&, double, double, at::CUDAGeneratorImpl*)), 2u>, float, float> >(at::TensorIterator&, at::CUDAGeneratorImpl*, __nv_dl_wrapper_t<__nv_dl_tag<void (*)(at::TensorIterator&, at::CUDAGeneratorImpl*, __nv_dl_wrapper_t<__nv_dl_tag<void (*)(at::Tensor&, double, double, at::CUDAGeneratorImpl*), &(void at::native::templates::cuda::normal_kernel<at::CUDAGeneratorImpl*>(at::Tensor&, double, double, at::CUDAGeneratorImpl*)), 2u>, float, float>), &(void at::native::templates::cuda::normal_and_transform<float, float, 4ul, at::CUDAGeneratorImpl*, __nv_dl_wrapper_t<__nv_dl_tag<void (*)(at::Tensor&, double, double, at::CUDAGeneratorImpl*), &(void at::native::templates::cuda::normal_kernel<at::CUDAGeneratorImpl*>(at::Tensor&, double, double, at::CUDAGeneratorImpl*)), 2u>, float, float> >(at::TensorIterator&, at::CUDAGeneratorImpl*, __nv_dl_wrapper_t<__nv_dl_tag<void (*)(at::Tensor&, double, double, at::CUDAGeneratorImpl*), &(void at::native::templates::cuda::normal_kernel<at::CUDAGeneratorImpl*>(at::Tensor&, double, double, at::CUDAGeneratorImpl*)), 2u>, float, float>)), 2u>> const&, __nv_dl_wrapper_t<__nv_dl_tag<void (*)(at::Tensor&, double, double, at::CUDAGeneratorImpl*), &(void at::native::templates::cuda::normal_kernel<at::CUDAGeneratorImpl*>(at::Tensor&, double, double, at::CUDAGeneratorImpl*)), 2u>, float, float>) + 0x76f (0x7f5e3f91602f in /dummy-libtorch/libtorch/lib/libtorch_cuda_cu.so)
frame #3: void at::native::templates::cuda::normal_kernel<at::CUDAGeneratorImpl*>(at::Tensor&, double, double, at::CUDAGeneratorImpl*) + 0x2f7 (0x7f5e3f917417 in /dummy-libtorch/libtorch/lib/libtorch_cuda_cu.so)
frame #4: at::native::normal_kernel(at::Tensor&, double, double, c10::optional<at::Generator>) + 0x17c (0x7f5e3f91441c in /dummy-libtorch/libtorch/lib/libtorch_cuda_cu.so)
frame #5: <unknown function> + 0xf51bea (0x7f5e2ca5bbea in /dummy-libtorch/libtorch/lib/libtorch_cpu.so)
frame #6: <unknown function> + 0xf52089 (0x7f5e2ca5c089 in /dummy-libtorch/libtorch/lib/libtorch_cpu.so)
frame #7: at::native::normal_(at::Tensor&, double, double, c10::optional<at::Generator>) + 0x23 (0x7f5e2ca52093 in /dummy-libtorch/libtorch/lib/libtorch_cpu.so)
frame #8: <unknown function> + 0xb916c8 (0x7f5e3eb0b6c8 in /dummy-libtorch/libtorch/lib/libtorch_cuda_cu.so)
frame #9: <unknown function> + 0xb91785 (0x7f5e3eb0b785 in /dummy-libtorch/libtorch/lib/libtorch_cuda_cu.so)
frame #10: <unknown function> + 0x1910934 (0x7f5e2d41a934 in /dummy-libtorch/libtorch/lib/libtorch_cpu.so)
frame #11: at::Tensor::normal_(double, double, c10::optional<at::Generator>) const + 0x91 (0x7f5e2d3fa901 in /dummy-libtorch/libtorch/lib/libtorch_cpu.so)
frame #12: at::native::randn(c10::ArrayRef<long>, c10::optional<at::Generator>, c10::TensorOptions const&) + 0x50 (0x7f5e2cca7f90 in /dummy-libtorch/libtorch/lib/libtorch_cpu.so)
frame #13: at::native::randn(c10::ArrayRef<long>, c10::TensorOptions const&) + 0x20 (0x7f5e2cca8080 in /dummy-libtorch/libtorch/lib/libtorch_cpu.so)
frame #14: <unknown function> + 0x17a9bf9 (0x7f5e2d2b3bf9 in /dummy-libtorch/libtorch/lib/libtorch_cpu.so)
frame #15: <unknown function> + 0x17a9e7a (0x7f5e2d2b3e7a in /dummy-libtorch/libtorch/lib/libtorch_cpu.so)
frame #16: <unknown function> + 0x167e899 (0x7f5e2d188899 in /dummy-libtorch/libtorch/lib/libtorch_cpu.so)
frame #17: <unknown function> + 0x1632c8e (0x7f5e2d13cc8e in /dummy-libtorch/libtorch/lib/libtorch_cpu.so)
frame #18: at::randn(c10::ArrayRef<long>, c10::TensorOptions) + 0x13b (0x7f5e2d00f9db in /dummy-libtorch/libtorch/lib/libtorch_cpu.so)
frame #19: torch::randn(c10::ArrayRef<long>, c10::TensorOptions) + 0x92 (0x55e493670271 in ./build/simple_model)
frame #20: main + 0x1b0 (0x55e49366bb10 in ./build/simple_model)
frame #21: __libc_start_main + 0xf3 (0x7f5db866a0b3 in /lib/x86_64-linux-gnu/libc.so.6)
frame #22: _start + 0x2e (0x55e49366b7fe in ./build/simple_model)

Aborted (core dumped)
```
