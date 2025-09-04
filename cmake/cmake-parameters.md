# CMake Parameters

## Required Parameters

## Optional Parameters

- `CMAKE_CXX_SCAN_FOR_MODULES`: Whether to use C++ modules.  
  See: [cmake/compilers/cxx-compiler-configs.cmake](../cmake/compilers/cxx-compiler-configs.cmake).  
  Default: `OFF`.  
  Possible values: `ON`, `OFF`.
- `CMAKE_CXX_STANDARD`: C++ standard.  
  See: [cmake/compilers/cxx-compiler-configs.cmake](../cmake/compilers/cxx-compiler-configs.cmake).  
  Default: *Auto-Detect*.  
  Possible values: `14`, `17`, `20`, `23`.
- `CMAKE_EXECUTABLE_SUFFIX`: Executable suffix.  
  See: [CMakelists.txt](../CMakeLists.txt).  
  Default: `.exe`.
- `ENV{CC}`: C compiler.  
  See: [cmake/compilers/cxx-compiler-configs.cmake](../cmake/compilers/cxx-compiler-configs.ckmake).  
  Default: *Auto-Detect*.  
  Possible values: `gcc`, `clang`, `cl`, etc.
- `ENV{CXX}`: C++ compiler.  
  See: [cmake/compilers/cxx-compiler-configs.cmake](../cmake/compilers/cxx-compiler-configs.cmake).  
  Default: *Auto-Detect*.  
  Possible values: `gcc++`, `clang++`, `cl`, etc.
- `STACK_SIZE`: Stack size for the executable targets (if any).  
  See: [cmake/compilers/cxx-compiler-configs.cmake](../cmake/compilers/cxx-compiler-configs.cmake).  
  Default: `1048576` (Bytes).