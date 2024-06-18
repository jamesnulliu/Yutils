#!/bin/bash

build_type="Debug"
lib_output_dir=""
bin_output_dir=""

if [ ! -z $1 ]; then
    if [ $1 != "Debug" ] && [ $1 != "Release" ]; then
        echo "Invalid build type. Please use either Debug or Release."
        exit 1
    else
        build_type=$1
    fi
fi

if [ ! -z $2 ]; then
    lib_output_dir=$2
fi

if [ ! -z $3 ]; then
    bin_output_dir=$3
fi

PROJECT_ROOT_DIR=$(pwd)

rm -rf $PROJECT_ROOT_DIR/build

mkdir -p $PROJECT_ROOT_DIR/build

cd $PROJECT_ROOT_DIR/build

cmake .. -DCMAKE_BUILD_TYPE=$build_type -DBUILD_TESTS=ON \
    -DLIB_OUTPUT_DIR=$lib_output_dir -DBIN_OUTPUT_DIR=$bin_output_dir

make -j $(nproc)

cd $PROJECT_ROOT_DIR

echo "Build finished successfully."