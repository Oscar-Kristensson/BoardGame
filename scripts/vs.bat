# Create a build directory
mkdir build
cd build


# Generate Visual Studio files (this step assumes you want to generate for Visual Studio 2022)
cmake -G "Visual Studio 17 2022" ..

@echo off
set /p answer=Do you want to build the project? (Y/N):

if /I "%answer%"=="Y" (
    @echo on
    cmake --build .
) else (
    echo You chose No.
)
