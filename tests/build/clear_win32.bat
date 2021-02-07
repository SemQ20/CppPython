echo off
rd /s /q CMakeFiles
rd /s /q __pycache__
del test.exe
del cmake_install.cmake
del CMakeCache.txt
del Makefile
cd ..