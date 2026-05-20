cmake_minimum_required(VERSION 3.14)
project(CodeforcesSolutions CXX)

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

    # Replace '.cpp' with '_debug.txt'
    string(REPLACE ".cpp" "_debug.txt" REL_TEST_PATH "${REL_SOURCE_PATH}")

    # Construct the absolute path to where the text file should be
    set(TEST_FILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tests/${REL_TEST_PATH}")

    # Generate the Invisible Injector C++ file
    # We create a temporary file in the build directory
    set(INJECTOR_FILE "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}_injector.cpp")
    
    # The C++ code that redirects stdin before main() starts
    file(WRITE "${INJECTOR_FILE}" "
    #include <cstdio>
    struct StdinRedirector {
        StdinRedirector() {
            fprintf(stderr, \"[Injector] Looking for: %s\\n\", \"${TEST_FILE_PATH}\");
            
            if (FILE* f = fopen(\"${TEST_FILE_PATH}\", \"r\")) {
                fclose(f); 
                freopen(\"${TEST_FILE_PATH}\", \"r\", stdin);
                fprintf(stderr, \"[Injector] Success: Reading from _debug.txt file!\\n\");
            } else {
                fprintf(stderr, \"[Injector] File not found. Waiting for keyboard input.\\n\");
            }
            fprintf(stderr, \"\\n\");
        }
    } redirector; // Create a global instance so it runs before main()
    ")

    # Compile BOTH your original code AND the injector together
    add_executable(${TARGET_NAME} ${SOURCE_FILE} ${INJECTOR_FILE})

endforeach()