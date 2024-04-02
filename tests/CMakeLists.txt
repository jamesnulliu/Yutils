cmake_minimum_required(VERSION 3.21)

Project(YutilsTests)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Link to Yutils library automatically
target_link_libraries(${PROJECT_NAME} PRIVATE Yutils)
# Or link to the library manually
# > target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/lib)

if (BUILD_SHARED_LIBS)
    # Define YUTILS_IMPORT when using the DLL, critical for windows
    target_compile_definitions(${PROJECT_NAME} PRIVATE YUTILS_IMPORT)
endif()

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY 
    ${PROJECT_SOURCE_DIR}/bin/exp02/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}
)