#!/bin/bash

echo "](@~@)[ BUILD START ]|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"

ProjHome=$(pwd)

# Default values
BuildType="Release"       # Build type: Release or Debug
BuildExamples="OFF"       # Build examples
Prefix="$ProjHome/build"  # Output directory
BuildSharedLibs="OFF"     # Build shared libraries
CleanFirst="false"        # Clean first before build
CleanAll="false"          # Remove all build files
NotBuild="false"          # Only generate build files, not build

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        Release|Debug)
            BuildType=$1
            ;;
        -nb|--not-build)
            NotBuild="true"
            ;;
        -be|--build-example)
            BuildExamples="ON"
            ;;
        --prefix=*)
            Prefix="${1#*=}"
            ;;
        --shared)
            BuildSharedLibs="ON"
            ;;
        -cf|--clean-first)
            Clean="true"
            ;;
        -ca|--clean-all)
            CleanAll="true"
            ;;
        *)
            echo "Error: Invalid argument '$1'"
            exit 1
            ;;
    esac
    shift
done

if [ "$CleanAll" = "true" ] && [ -d "$ProjHome/build" ]; then
    echo "[build.sh] Removing all build files..."
    rm -rf $ProjHome/build
fi

if [ ! -d $ProjHome/build ]; then
    mkdir -p $ProjHome/build
fi

cd $ProjHome/build

cmake ..  \
    -DCMAKE_BUILD_TYPE=$BuildType \
    -DBUILD_EXAMPLES=$BuildExamples  \
    -DOUTPUT_DIR=$Prefix  \
    -DBUILD_SHARED_LIBS=$BuildSharedLibs \
    -G="Ninja"

if [ "$NotBuild" = "false" ]; then
    if [ "$CleanFirst" = "true" ]; then
        cmake --build . --parallel $(nproc) --clean-first
    else
        cmake --build . --parallel $(nproc)
    fi
fi

cd $ProjHome

echo "](OvO)[ BUILD FINISHED ]||||||||||||||||||||||||||||||||||||||||||||||||||||||||"

if [ $BuildSharedLibs = "ON" ]; then
    echo "[build.sh] Note:"
    echo "| You have built Yutils as a shared library."
    echo "| If you are using Windows, you may need to:"
    echo "|   - Copy the DLL files to the directory where the executable is located."
    echo "|   OR"
    echo "|   - Add the directory where the DLL files are located to the PATH environment variable."
    echo "| If you are using Linux, you may need to:"
    echo "|   - Add the directory where the shared library files are located to the LD_LIBRARY_PATH environment variable."
fi