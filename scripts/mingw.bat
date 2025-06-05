mkdir build
cd build

cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Dist ..

cmake --build .

cd ..
@echo off
set /p answer=Do you want to run the executable? (Y/N):

if /I "%answer%"=="Y" (
    @echo on
    "build/bin/Dist/game.exe"
) else (
    echo You chose No.
)