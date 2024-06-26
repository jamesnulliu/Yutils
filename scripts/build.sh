#!/bin/bash

ProjHome=$(pwd)

# Default values
BuildType="Release"
BuildTest="OFF"
Prefix=$ProjHome
BuildSharedLibs="OFF"
Clean="false"
CleanAll="false"

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        Release|Debug)
            BuildType=$1
            ;;
        -t|--test)
            BuildTest="ON"
            ;;
        --prefix=*)
            Prefix="${1#*=}"
            ;;
        --shared)
            BuildSharedLibs="ON"
            ;;
        -c|--clean)
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
    echo "Cleaning all build files..."
    rm -rf $ProjHome/build
fi

if [ ! -d $ProjHome/build ]; then
    mkdir -p $ProjHome/build
fi

cd $ProjHome/build

cmake ..  \
    -DCMAKE_BUILD_TYPE=$BuildType \
    -DBUILD_TESTS=$BuildTest  \
    -DOUTPUT_DIR=$Prefix  \
    -DBUILD_SHARED_LIBS=$BuildSharedLibs \
    -G="Ninja"

if [ "$Clean" = "true" ]; then
    cmake --build . --parallel $(nproc) --clean-first
else
    cmake --build . --parallel $(nproc)
fi

cd $ProjHome

echo "[Yutils] Build finished."

if [ $BuildSharedLibs = "ON" ]; then
    echo "[Yutils|Note]:"
    echo "| You have built Yutils as a shared library."
    echo "| If you are using Windows, you may need to:"
    echo "|   - Copy the DLL files to the directory where the executable is located."
    echo "|   OR"
    echo "|   - Add the directory where the DLL files are located to the PATH environment variable."
    echo "| If you are using Linux, you may need to:"
    echo "|   - Add the directory where the shared library files are located to the LD_LIBRARY_PATH environment variable."
fi