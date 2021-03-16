rm -rf build
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=$PWD/../libtorch ..
cmake --build . --config Release
