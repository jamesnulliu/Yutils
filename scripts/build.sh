#!/bin/bash

PROJECT_ROOT_DIR=$(pwd)

# Default values
BuildType="Release"
BuildTest="OFF"
LibOutputDir="${PROJECT_ROOT_DIR}/lib"
BuildSharedLibs="OFF"

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
        *)
            echo "Error: Invalid argument '$1'"
            exit 1
            ;;
    esac
    shift
done

rm -rf $PROJECT_ROOT_DIR/build

mkdir -p $PROJECT_ROOT_DIR/build

cd $PROJECT_ROOT_DIR/build

cmake ..  \
    -DCMAKE_BUILD_TYPE=$BuildType \
    -DBUILD_TESTS=$BuildTest  \
    -DLIB_OUTPUT_DIR=$LibOutputDir  \
    -DBUILD_SHARED_LIBS=$BuildSharedLibs \
    -G="Ninja"

cmake --build . --parallel $(nproc)

cd $PROJECT_ROOT_DIR

echo "Build finished."