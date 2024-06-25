$ProjHome = Get-Location

# Default values
$BuildMode = "Release"
$BuildTest = "OFF"
$LibOutputDir = "$ProjHome/lib"
$BuildSharedLibs = "OFF"
$CleanFirst = $false
$CleanAll = $false

# Parse arguments
for ($i = 0; $i -lt $args.Count; $i++) {
    switch ($args[$i]) {
        "Release" { $BuildMode = "Release" }
        "Debug" { $BuildMode = "Debug" }
        "-t"{ $BuildTest = "ON" }
        "--test" { $BuildTest = "ON" }
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
        "--shared" { $BuildSharedLibs = "ON" }
        "-c" { $CleanFirst = $true }
        "--clean" { $CleanFirst = $true }
        "-ca" { $CleanAll = $true }
        "--clean-all" { $CleanAll = $true }
        default {
            Write-Host "Error: Invalid argument '$($args[$i])'"
            exit 1
        }
    }
}

if ($CleanAll -and (Test-Path "$ProjHome/build")) {
    Write-Host "Cleaning all build files..."
    Remove-Item "$ProjHome/build" -Recurse -Force
}
if (-not (Test-Path "$ProjHome/build")) {
    New-Item -ItemType Directory -Path "$ProjHome/build"
}

Set-Location "$ProjHome/build"

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

Set-Location $ProjHome

Write-Host "Build finished."
