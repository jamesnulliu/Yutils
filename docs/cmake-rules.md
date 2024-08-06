# CMake Rules

`CMAKE_BUILD_TYPE`  
**Brief**: The build type to use for the project.  
**Value**: [Release, Debug]  
**Default**: Release  

`OUTPUT_DIR`  
**Brief**: The directory where the project will be built.  After a successful build, "lib" and "include" directory will be created in the \${OUTPUT_DIR}.  
**Value**: /path/to/output/directory  
**Default**: ${CMAKE_CURRENT_SOURCE_DIR}  
    
`BUILD_SHARED_LIBS`  
**Brief**: Whether to build Yutils as a shared library.  
**Value**: [ON, OFF]  
**Default**: OFF  