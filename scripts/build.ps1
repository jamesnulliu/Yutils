# Default values
$BuildMode = "Debug"
$BuildTest = "OFF"
$LibOutputDir = ""
$BuildSharedLibs = "OFF"

# Parse arguments
for ($i = 0; $i -lt $args.Count; $i++) {
    switch ($args[$i]) {
        "Release" {
            $BuildMode = "Release"
        }
        "Debug" {
            $BuildMode = "Debug"
        }
        "-t"{
            $BuildTest = "ON"
        }
        "--test" {
            $BuildTest = "ON"
        }
        "--libo" {
            $i++
            if ($i -lt $args.Count -and $args[$i]) {
                $LibOutputDir = $args[$i]
            }
            else {
                Write-Host "Error: '--libo' requires a directory path as the next argument."
                exit 1
            }
        }
        "--shared" {
            $BuildSharedLibs = "ON"
        }
        default {
            Write-Host "Error: Invalid argument '$($args[$i])'"
            exit 1
        }
    }
}

# Output the parsed values
Write-Host "BUILD_MODE: $BuildMode"
Write-Host "BUILD_TEST: $BuildTest"
Write-Host "LIB_OUTPUT_DIR: $LibOutputDir"
Write-Host "BUILD_SHARED_LIBS: $BuildSharedLibs"


$PROJECT_ROOT_DIR = Get-Location

if (Test-Path "$PROJECT_ROOT_DIR/build") {
    Remove-Item "$PROJECT_ROOT_DIR/build" -Recurse -Force
}

New-Item -ItemType Directory -Path "$PROJECT_ROOT_DIR/build"

Set-Location "$PROJECT_ROOT_DIR/build"

$CMakeArgs = @(
    "-DCMAKE_BUILD_TYPE=$BuildMode",
    "-DBUILD_TESTS=$BuildTest",
    "-DLIB_OUTPUT_DIR=$LibOutputDir",
    "-DBUILD_SHARED_LIBS=$BuildSharedLibs"
)

& cmake .. $CMakeArgs

& cmake --build . --config $BuildMode

Set-Location $PROJECT_ROOT_DIR

Write-Host "Build finished."