mkdir build
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER="C:/mingw64/bin/g++.exe"
cmake --build build