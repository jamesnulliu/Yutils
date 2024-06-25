# @Path: Yutils/tests/CMakeLists.txt

# Minimum required CMake version
cmake_minimum_required(VERSION 3.21)

Project(YutilsTests)  

# # Set C++ standard to C++23
# set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(
    ${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(${PROJECT_NAME} PRIVATE Yutils)

# if (BUILD_SHARED_LIBS)
#     target_compile_definitions(${PROJECT_NAME} PRIVATE YUTILS_IMPORT)
# endif()

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY 
    ${OUTPUT_DIR}/tests/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}
)