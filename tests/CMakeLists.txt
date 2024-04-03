# @Path: Yutils/tests/CMakeLists.txt

# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)

# PROJECT_NAME: YutilsTests
Project(YutilsTests)  

# Output binary name: YutilsTests
add_executable(${PROJECT_NAME} main.cpp)

# Set target include directories:
# - Yutils/include
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Link to Yutils library automatically
# @see Yutils/src/CMakeLists.txt: add_library(${LIBRARY_NAME} ...)
target_link_libraries(${PROJECT_NAME} PRIVATE Yutils)
# Or link to the library manually
# > target_link_libraries(${PROJECT_NAME} PRIVATE ../lib)

if (BUILD_SHARED_LIBS)
    # Define YUTILS_IMPORT when using the DLL, critical for windows
    target_compile_definitions(${PROJECT_NAME} PRIVATE YUTILS_IMPORT)
endif()

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY 
    ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}
)