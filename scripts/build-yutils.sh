if [ -z "$SPDLOG_HOME" ]; then
    echo "SPDLOG_HOME is not set"
    exit 1
fi

cmake -G Ninja -S . -B ./build \
    -DCMAKE_CXX_STANDARD=23 \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=OFF \
    -DYUTILS_BUILD_EXAMPLES=ON \
    -DSPDLOG_HOME=$SPDLOG_HOME

cmake --build ./build --parallel $(nproc)

