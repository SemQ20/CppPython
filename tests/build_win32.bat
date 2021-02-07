echo off
cd build
cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" .. && make && test.exe && cd ..