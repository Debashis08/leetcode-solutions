# leetcode solutions

## First-Time Setup (CMake Presets)

This repository utilizes a `CMakePresets.json` file configured for the Ninja generator and the MSVC compiler (`cl.exe`).

**For VS Code / Visual Studio Users:**

- Open the repository folder in your IDE; it will automatically detect the `CMakePresets.json` file.
- Select the **`x64-debug`** preset from the CMake dropdown menu located in your bottom status bar. The IDE will handle the environment setup perfectly.

**For Terminal Users:**

- You must open the **"Developer Command Prompt for VS"** (do not use standard PowerShell) to ensure the compiler environment variables are properly loaded.
- Configure the project: `cmake --preset x64-debug`.
- Build the project: `cmake --build --preset x64-debug`.

> **Note:** The `x64-debug` preset is highly recommended for daily problem-solving. It enables C++ standard library assertions, which will instantly catch out-of-bounds memory errors locally rather than throwing vague Runtime Errors on LeetCode.
> 

This repository provides a highly optimized local testing and debugging environment for competitive programming. It utilizes a custom C++ script to generate boilerplate code and a powerful CMake configuration that automatically pipes test case data directly into your programs.

## Generating Boilerplate Code

To eliminate manual folder navigation and copy-pasting, use the automated generator script located in the root directory.

- Double-click `generate.bat` or run it from your terminal.
- Enter the Problem ID (e.g., `3658` or `282A`).
- The script calculates the correct folder bucket (e.g., `3600-3699`).
- It automatically creates the `.cpp` solution file in the `src/` directory.
- It creates a mirrored `.txt` test file in the `tests/` directory using your root templates.

## Running Tests

Your localized test runners are tucked away inside the `tests/scripts/` folder to keep your root directory perfectly clean.

- **Run a Single Test:** Execute `run-single-test.bat`, which will prompt you for a Problem ID, compile that specific runner, and evaluate your outputs.
- **Run All Tests:** Execute `run-all-tests.bat` to scan your test directories and validate your entire problem suite.
- Both scripts automatically navigate to the repository root before compiling, ensuring paths resolve correctly.

## Debugging with the Invisible Injector

Typing inputs manually during debugging is tedious. This workspace uses a CMake-generated "Invisible Injector" that redirects `std::cin` to read directly from a text file before your `main()` function even starts.

- **File Placement:** Your debug text file must mirror the `src/` directory structure but include an extra `debug/` folder level (e.g., `tests/2600-2699/debug/2657_debug.txt`).
- **Raw Data Only:** The debug file must contain raw input numbers only.
- **No Labels:** Do not include words like "Test Case 1:" or "Input:", as `std::cin` will fail and crash your program with Exit Code 3.
- **Target Selection:** Use your IDE's CMake extension (bottom status bar) to select the specific problem's executable target.
- **Execution:** Click the CMake debugger button; you will see a `[Injector] Success` message in the console as your breakpoints populate.

## Core Utility Classes

LeetCode handles complex data structure serialization behind the scenes. You can use the local `Core` class to seamlessly replicate this behavior. Simply include `#include "core.h"` in your solution file to access these static helper methods.

- **Linked Lists:** Use `Core::createLinkedList(nums)` to instantly convert a `std::vector<int>` into a fully linked `ListNode` chain. Verify your output using `Core::printList(head)`.
- **Binary Trees:** When your solution returns a `TreeNode*`, use `Core::printBinaryTreeInLevelOrder(root)` to print the tree exactly in LeetCode's compact Breadth-First Search (BFS) array format.
- **Vectors:** Easily format and verify your array answers using `Core::printVectorResult(result)` for 1D arrays or `Core::printTwoDimensionalVectorResult(result)` for matrices.
