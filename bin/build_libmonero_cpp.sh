#!/bin/sh

HOST_NCORES=$(nproc 2>/dev/null || shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 1)

# Make libmonero-cpp.dylib
cd ./external/monero-core/ && 
make release-static -j$HOST_NCORES &&

# Make libmonero-cpp.dylib
cd ../../ &&
mkdir -p build && 
cd build && 
cmake .. && 
cmake --build . -j$HOST_NCORES && 
make .