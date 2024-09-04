# Yutils

## Required Libraries

### spdlog

```bash
# Clone the spdlog project
export SPDLOG_PROJECT_DIR="/path/to/spdlog"
git clone https://github.com/gabime/spdlog.git  "${SPDLOG_PROJECT_DIR}"

export SPDLOG_HOME="${SPDLOG_PROJECT_DIR}/spdlog"

bash ./scripts/install-spdlog.sh Release --std-format
```

## Build

```bash
bash scripts/build-yutils.sh
```

## Install

```bash
bash scripts/install-yutils.sh
```