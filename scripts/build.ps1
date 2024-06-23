$PROJECT_ROOT_DIR = Get-Location

# Default values
$BuildMode = "Release"
$BuildTest = "OFF"
$LibOutputDir = "$PROJECT_ROOT_DIR/lib"
$BuildSharedLibs = "OFF"
$CleanFirst = $false

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
        "-c" {
            $CleanFirst = $true
        }
        "--clean-first" {
            $CleanFirst = $true
        }
        default {
            Write-Host "Error: Invalid argument '$($args[$i])'"
            exit 1
        }
    }
}

if (-not (Test-Path "$PROJECT_ROOT_DIR/build")) {
    New-Item -ItemType Directory -Path "$PROJECT_ROOT_DIR/build"
}

Set-Location "$PROJECT_ROOT_DIR/build"

$CMakeArgs = @(
    "-DCMAKE_BUILD_TYPE=$BuildMode",
    "-DBUILD_TESTS=$BuildTest",
    "-DLIB_OUTPUT_DIR=$LibOutputDir",
    "-DBUILD_SHARED_LIBS=$BuildSharedLibs",
    "-G=Ninja"
)

& cmake .. $CMakeArgs

$BuildArgs = @(
    "--parallel",
    "$env:NUMBER_OF_PROCESSORS"
)
if ($CleanFirst) { $BuildArgs += "--clean-first" }

& cmake --build . $BuildArgs

Set-Location $PROJECT_ROOT_DIR

Write-Host "Build finished."
