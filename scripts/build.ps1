$ProjHome = Get-Location

# Default values
$BuildMode = "Release"
$BuildTest = "OFF"
$Prefix = $ProjHome
$BuildSharedLibs = "OFF"
$Clean = $false
$CleanAll = $false

# Parse arguments
for ($i = 0; $i -lt $args.Count; $i++) {
    switch ($args[$i]) {
        "Release" { $BuildMode = "Release" }
        "Debug" { $BuildMode = "Debug" }
        "-t"{ $BuildTest = "ON" }
        "--test" { $BuildTest = "ON" }
        "--prefix" {
            $i++
            if ($i -lt $args.Count -and $args[$i]) {
                $Prefix = $args[$i]
            }
            else {
                Write-Host "Error: '--prefix' requires a directory path as the next argument."
                exit 1
            }
        }
        "--shared" { $BuildSharedLibs = "ON" }
        "-c" { $Clean = $true }
        "--clean" { $Clean = $true }
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
    "-DOUTPUT_DIR=$Prefix",
    "-DBUILD_SHARED_LIBS=$BuildSharedLibs",
    "-G=Ninja"
)

& cmake .. $CMakeArgs

$BuildArgs = @(
    "--parallel",
    "$env:NUMBER_OF_PROCESSORS"
)
if ($Clean) { $BuildArgs += "--clean-first" }

& cmake --build . $BuildArgs

Set-Location $ProjHome

Write-Host "Build finished."
