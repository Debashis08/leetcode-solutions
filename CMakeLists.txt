cmake_minimum_required(VERSION 3.14)
project(LeetCodeSolutions CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Auto-discover all source files in the src folder
file(GLOB_RECURSE PROBLEM_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Loop through and generate executables
foreach(SOURCE_FILE IN LISTS PROBLEM_FILES)
    
    # Extract just the file name
    get_filename_component(TARGET_NAME ${SOURCE_FILE} NAME_WE)

    # Get the relative path of the .cpp file starting from the src folder
    file(RELATIVE_PATH REL_SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src" "${SOURCE_FILE}")

    # Extract the directory part of the relative path
    get_filename_component(REL_DIR_PATH "${REL_SOURCE_PATH}" DIRECTORY)

    # Construct the absolute path, injecting the "debug" folder
    # If the file is directly in src/ (no subfolder), handle it cleanly
    if(REL_DIR_PATH STREQUAL "")
        set(TEST_FILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tests/debug/${TARGET_NAME}_debug.txt")
    else()
        set(TEST_FILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tests/${REL_DIR_PATH}/debug/${TARGET_NAME}_debug.txt")
    endif()

    # Create a temporary file in the build directory
    set(INJECTOR_FILE "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}_injector.cpp")
    
    # The C++ code that redirects stdin before main() starts
    file(WRITE "${INJECTOR_FILE}" "
    #include <cstdio>
    struct StdinRedirector {
        StdinRedirector() {
            fprintf(stderr, \"[Injector] Looking for: %s\\n\", \"${TEST_FILE_PATH}\");
            
            FILE* f = nullptr;
            // fopen_s returns 0 on success and takes the FILE* by reference
            if (fopen_s(&f, \"${TEST_FILE_PATH}\", \"r\") == 0) {
                if (f) fclose(f); 
                
                FILE* stream = nullptr;
                // freopen_s also returns 0 on success and takes the FILE* by reference
                freopen_s(&stream, \"${TEST_FILE_PATH}\", \"r\", stdin);
                
                fprintf(stderr, \"[Injector] Success: Reading from _debug.txt file!\\n\");
            } else {
                fprintf(stderr, \"[Injector] File not found. Waiting for keyboard input.\\n\");
            }
            fprintf(stderr, \"\\n\");
        }
    } redirector; // Create a global instance so it runs before main()
    ")

    # Compile BOTH your original code AND the injector together [cite: 73]
    add_executable(${TARGET_NAME} ${SOURCE_FILE} ${INJECTOR_FILE})

endforeach()