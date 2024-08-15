# Yutils

## Required Libraries

### spdlog

```bash
git clone https://github.com/gabime/spdlog.git 
cd ./spdlog
cmake -S . -B ./build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DSPDLOG_BUILD_SHARED=ON
cmake --build ./build
cmake --install ./build --prefix ./spdlog

export SPDLOG_DIR=$(pwd)/spdlog
```