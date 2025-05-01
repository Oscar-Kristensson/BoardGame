# Create a build directory
mkdir build
cd build


# Generate Visual Studio files (this step assumes you want to generate for Visual Studio 2022)
cmake -G "Visual Studio 17 2022" ..

# Now build the project
