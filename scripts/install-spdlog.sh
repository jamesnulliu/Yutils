
SpdlogProjectDir=${SPDLOG_PROJECT_DIR}
SpdlogInstallDir=${SPDLOG_HOME}
BuildType=Release
BuildSharedLibs=OFF
BuildExample=OFF
UseStdFormat=OFF

while [[ $# -gt 0 ]]; do
    case $1 in
        --src=*)
            SpdlogProjectDir="${1#*=}"
            ;;
        --prefix=*)
            SpdlogInstallDir="${1#*=}"
            ;;
        Release|Debug)
            BuildType=$1
            ;;
        --build-example)
            BuildExample="ON"
            ;;
        --shared)
            BuildSharedLibs="ON"
            ;;
        --std-format)
            UseStdFormat="ON"
            ;;
        *)
            echo "Error: Invalid argument '$1'"
            exit 1
            ;;
    esac
    shift
done

# If the project directory does not exist, clone it from the repo
if [ ! -d "$SpdlogProjectDir" ]; then
    echo -e "\033[0;32mCloning spdlog...\033[0m"
    git clone https://github.com/gabime/spdlog.git $SPDLOG_PROJECT_DIR
fi

echo -e "\033[0;32mBuilding spdlog...\033[0m"

pushd $SpdlogProjectDir
    rm -rf build

    cmake -G Ninja -B ./build -S . \
        -DCMAKE_BUILD_TYPE=$BuildType \
        -DSPDLOG_BUILD_SHARED=$BuildSharedLibs \
        -DSPDLOG_ENABLE_PCH=ON \
        -DSPDLOG_BUILD_PIC=ON \
        -DSPDLOG_USE_STD_FORMAT=$UseStdFormat \
        -DSPDLOG_BUILD_EXAMPLE=$BuildExample

    cmake --build ./build -j 8

    rm -rf $SpdlogInstallDir

    cmake --install ./build --prefix $SpdlogInstallDir
popd

echo -e "\033[0;32mFinished building spdlog.\033[0m"

echo "Configuration:"
echo "  Project Dir: $SpdlogProjectDir"
echo "  Install Dir: $SpdlogInstallDir"
echo "  Build Type: $BuildType"
echo "  Build Shared Libs: $BuildSharedLibs"
echo "  Build Example: $BuildExample"
echo "  Use Std Format: $UseStdFormat"
