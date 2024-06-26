$ProjHome = Get-Location

# Default values
$BuildType = "Release"
$BuildTest = "OFF"
$Prefix = $ProjHome
$BuildSharedLibs = "OFF"
$Clean = $false
$CleanAll = $false

# Parse arguments
for ($i = 0; $i -lt $args.Count; $i++) {
    if ($args[$i] -match '^--prefix=(.*)$') {
        $Prefix = $Matches[1]  # Extracts the part after '='
        continue
    }
    switch ($args[$i]) {
        "Release" { $BuildType = "Release" }
        "Debug" { $BuildType = "Debug" }
        "-t"{ $BuildTest = "ON" }
        "--test" { $BuildTest = "ON" }
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
    "-DCMAKE_BUILD_TYPE=$BuildType",
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

Write-Host "[Yutils] Build finished."

if ($BuildSharedLibs -eq "ON") {
    Write-Host "[Yutils|Note]:" 
    Write-Host "| You have built Yutils as a shared library."
    Write-Host "| If you are using Windows, you may need to:"
    Write-Host "|   - Copy the DLL files to the directory where the executable is located."
    Write-Host "|   OR"
    Write-Host "|   - Add the directory where the DLL files are located to the PATH environment variable."
    Write-Host "| If you are using Linux, you may need to:"
    Write-Host "|   - Add the directory where the shared library files are located to the LD_LIBRARY_PATH environment variable."
}