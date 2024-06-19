#!/bin/bash

# Default values
BUILD_MODE="Debug"
BUILD_TEST="OFF"
LIB_OUTPUT_DIR=""
BIN_OUTPUT_DIR=""
BUILD_SHARED_LIBS="OFF"

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        Release|Debug)
            BUILD_MODE=$1
            ;;
        -t|--test)
            BUILD_TEST="ON"
            ;;
        --libo)
            if [[ -n $2 ]]; then
                LIB_OUTPUT_DIR=$2
                shift
            else
                echo "Error: '--libo' requires a directory path as the next argument."
                exit 1
            fi
            ;;
        --shared)
            BUILD_SHARED_LIBS="ON"
            ;;
        *)
            echo "Error: Invalid argument '$1'"
            exit 1
            ;;
    esac
    shift
done

PROJECT_ROOT_DIR=$(pwd)

rm -rf $PROJECT_ROOT_DIR/build

mkdir -p $PROJECT_ROOT_DIR/build

cd $PROJECT_ROOT_DIR/build

cmake ..  \
    -DCMAKE_BUILD_TYPE=$build_type  \
    -DBUILD_TESTS=ON  \
    -DLIB_OUTPUT_DIR=$lib_output_dir  \
    -DBUILD_SHARED_LIBS=$build_shared_libs

make -j $(nproc)

cd $PROJECT_ROOT_DIR

echo "Build finished."