#!/bin/bash

ProjHome=$(pwd)

# Default values
BuildType="Release"
BuildTest="OFF"
LibOutputDir="${ProjHome}/lib"
BuildSharedLibs="OFF"
CleanFirst="false"
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
        --libo)
            if [[ -n $2 ]]; then
                LibOutputDir=$2
                shift
            else
                echo "Error: '--libo' requires a directory path as the next argument."
                exit 1
            fi
            ;;
        --shared)
            BuildSharedLibs="ON"
            ;;
        -c|--clean)
            CleanFirst="true"
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
    -DLIB_OUTPUT_DIR=$LibOutputDir  \
    -DBUILD_SHARED_LIBS=$BuildSharedLibs \
    -G="Ninja"

if [ "$CleanFirst" = "true" ]; then
    cmake --build . --parallel $(nproc) --clean-first
else
    cmake --build . --parallel $(nproc)
fi

cd $ProjHome

echo "Build finished."