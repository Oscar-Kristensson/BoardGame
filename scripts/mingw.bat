mkdir build
cd build
cmake ..

cd ..
cmake -G "MinGW Makefiles"

cmake --build .

@echo off
set /p answer=Do you want to run the executable? (Y/N):

if /I "%answer%"=="Y" (
    @echo on
    "build/game.exe"
) else (
    echo You chose No.
)