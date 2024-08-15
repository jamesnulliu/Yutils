cmake -G Ninja -S . -B ./build \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=ON \
    -DYUTILS_BUILD_EXAMPLES=ON \
    -DSPDLOG_DIR=$SPDLOG_DIR

cmake --build ./build --parallel $(nproc) --clean-first

