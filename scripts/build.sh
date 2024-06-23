#!/bin/bash

PROJECT_ROOT_DIR=$(pwd)

# Default values
BuildType="Release"
BuildTest="OFF"
LibOutputDir="${PROJECT_ROOT_DIR}/lib"
BuildSharedLibs="OFF"
CleanFirst="false"

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
        *)
            echo "Error: Invalid argument '$1'"
            exit 1
            ;;
    esac
    shift
done

if [ ! -d $PROJECT_ROOT_DIR/build ]; then
    mkdir -p $PROJECT_ROOT_DIR/build
fi

cd $PROJECT_ROOT_DIR/build

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

cd $PROJECT_ROOT_DIR

echo "Build finished."