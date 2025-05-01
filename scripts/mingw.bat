mkdir build
cd build
cmake ..

cd ..
cmake -G "MinGW Makefiles"

cmake --build .
