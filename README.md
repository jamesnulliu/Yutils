# Yutils

## Required Libraries

### spdlog

```bash
# Clone the spdlog project
export SPDLOG_PROJECT_DIR="/path/to/spdlog/project/dir"
git clone https://github.com/gabime/spdlog.git  "${SPDLOG_PROJECT_DIR}"

export SPDLOG_HOME="path/to/spdlog/installation/dir"

bash ./scripts/build-and-install-spdlog.sh Release
```

## Build

```bash
bash scripts/build-yutils.sh
```

## Install

```bash
cmake --install ./build --prefix <install_dir>
```